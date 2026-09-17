// Simulated channel host-only crypto profile; fixed benchmark key, seed 7446529.
// Build: c++ -O3 -std=c++23 -Iinclude scripts/profile_aead.cpp build/libgoblin_cannon.a -lcrypto -o build/profile_aead
#include "goblin_cannon/crypto.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

using namespace goblin_cannon;
using Clock=std::chrono::steady_clock;
double us(Clock::time_point begin,Clock::time_point end) {return std::chrono::duration<double,std::micro>(end-begin).count();}
void percentiles(std::vector<double>& times) {
  std::sort(times.begin(),times.end());
  std::cout<<"{\"p50\":"<<times[times.size()/2-1]<<",\"p99\":"<<times[times.size()*99/100-1]
           <<",\"p99_9\":"<<times[times.size()*999/1000-1]<<",\"max\":"<<times.back()<<'}';
}
int main() {
  constexpr unsigned count=20000,warmup=1000;
  Aes256Key key{};std::uint64_t epoch=1;
  std::cout<<"{\"report_header\":\"simulated channel AES-256-GCM host profile\",\"seed\":7446529,\"iterations\":"<<count
           <<",\"warmup\":"<<warmup<<",\"scope\":\"Reused EVP contexts; GCM seal/open only, including verified plaintext copy and scratch cleansing; excludes FEC, framing and nonce-journal startup\",\"cases\":[";
  for (std::size_t size:{3U,16U,128U,1024U,65534U}) {
    const auto begin=Clock::now();Aes256Gcm cipher(key);const auto initialized=Clock::now();
    std::vector<std::uint8_t> input(size,71),encrypted,output;GcmTag tag{};
    const std::array<std::uint8_t,25> ad{1,0,1};
    std::vector<double> seal,open;seal.reserve(count);open.reserve(count);
    for (unsigned i=1;i<=count+warmup;++i) {
      const auto nonce=message_nonce(epoch,i);
      const auto a=Clock::now();cipher.seal(nonce,ad,input,encrypted,tag);const auto b=Clock::now();
      const bool valid=cipher.open(nonce,ad,encrypted,tag,output);const auto c=Clock::now();
      if (!valid || output!=input) return 1;
      if (i>warmup) {seal.push_back(us(a,b));open.push_back(us(b,c));}
    }
    if (epoch>1)std::cout<<',';
    std::cout<<"{\"body_bytes\":"<<size<<",\"context_initialization_us\":"<<us(begin,initialized)<<",\"seal_us\":";
    percentiles(seal);std::cout<<",\"open_us\":";percentiles(open);std::cout<<'}';++epoch;
  }
  std::cout<<"]}\n";
}
