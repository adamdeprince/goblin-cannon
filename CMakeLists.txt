cmake_minimum_required(VERSION 3.24)

project(
  wbhf_modem
  VERSION 0.1.0
  DESCRIPTION "Low-latency complex-baseband WBHF QAM/PSK modem library"
  LANGUAGES CXX)

option(WBHF_MODEM_BUILD_EXAMPLES "Build example programs" ON)
option(WBHF_MODEM_BUILD_TESTS "Build tests" ON)
add_library(wbhf_modem
  src/accounting.cpp
  src/control_server.cpp
  src/constellation.cpp
  src/client_udp.cpp
  src/convolutional.cpp
  src/crypto.cpp
  src/demapper.cpp
  src/frame.cpp
  src/integer_codec.cpp
  src/io.cpp
  src/market_data_shm.cpp
  src/message_stream.cpp
  src/modem.cpp
  src/quote_udp.cpp
  src/rf_stream.cpp
)

add_library(wbhf_modem::wbhf_modem ALIAS wbhf_modem)

target_compile_features(wbhf_modem PUBLIC cxx_std_23)
target_include_directories(
  wbhf_modem
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_definitions(wbhf_modem PRIVATE WBHF_MODEM_VERSION="${PROJECT_VERSION}")

find_package(OpenSSL REQUIRED COMPONENTS Crypto)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_program(WBHF_MODEM_GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)

target_link_libraries(wbhf_modem PUBLIC OpenSSL::Crypto protobuf::libprotobuf gRPC::grpc++)

set(WBHF_MODEM_PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
set(WBHF_MODEM_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(WBHF_MODEM_CONTROL_PROTO "${WBHF_MODEM_PROTO_DIR}/wbhf_modem/control/v1/receiver_control.proto")
set(WBHF_MODEM_CONTROL_PROTO_SRCS
    "${WBHF_MODEM_GENERATED_DIR}/wbhf_modem/control/v1/receiver_control.pb.cc"
    "${WBHF_MODEM_GENERATED_DIR}/wbhf_modem/control/v1/receiver_control.grpc.pb.cc")
set(WBHF_MODEM_CONTROL_PROTO_HDRS
    "${WBHF_MODEM_GENERATED_DIR}/wbhf_modem/control/v1/receiver_control.pb.h"
    "${WBHF_MODEM_GENERATED_DIR}/wbhf_modem/control/v1/receiver_control.grpc.pb.h")

add_custom_command(
  OUTPUT ${WBHF_MODEM_CONTROL_PROTO_SRCS} ${WBHF_MODEM_CONTROL_PROTO_HDRS}
  COMMAND ${CMAKE_COMMAND} -E make_directory "${WBHF_MODEM_GENERATED_DIR}"
  COMMAND ${Protobuf_PROTOC_EXECUTABLE}
          --proto_path=${WBHF_MODEM_PROTO_DIR}
          --cpp_out=${WBHF_MODEM_GENERATED_DIR}
          --grpc_out=${WBHF_MODEM_GENERATED_DIR}
          --plugin=protoc-gen-grpc=${WBHF_MODEM_GRPC_CPP_PLUGIN}
          ${WBHF_MODEM_CONTROL_PROTO}
  DEPENDS "${WBHF_MODEM_CONTROL_PROTO}"
  VERBATIM)

target_sources(wbhf_modem PRIVATE ${WBHF_MODEM_CONTROL_PROTO_SRCS})
target_include_directories(wbhf_modem PRIVATE "${WBHF_MODEM_GENERATED_DIR}")

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)

if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
  message(FATAL_ERROR "wbhf_modem requires an x86_64 AVX-512 host build.")
endif()

check_cxx_compiler_flag("-march=native" WBHF_MODEM_COMPILER_HAS_MARCH_NATIVE)
if(NOT WBHF_MODEM_COMPILER_HAS_MARCH_NATIVE)
  message(FATAL_ERROR "wbhf_modem requires compiler support for -march=native.")
endif()

set(CMAKE_REQUIRED_FLAGS "-march=native")
check_cxx_source_compiles(
  "#include <immintrin.h>
   int main() {
     __m512 v = _mm512_set1_ps(1.0f);
     return static_cast<int>(_mm512_reduce_add_ps(v));
   }"
  WBHF_MODEM_HOST_COMPILES_AVX512)
unset(CMAKE_REQUIRED_FLAGS)

if(NOT WBHF_MODEM_HOST_COMPILES_AVX512)
  message(FATAL_ERROR "wbhf_modem requires a host/compiler combination that supports AVX-512 with -march=native.")
endif()

set(CMAKE_REQUIRED_FLAGS "-march=native")
check_cxx_source_runs(
  "#include <immintrin.h>
   int main() {
     if (!__builtin_cpu_supports(\"avx512f\")) return 1;
     if (!__builtin_cpu_supports(\"avx512dq\")) return 2;
     if (!__builtin_cpu_supports(\"avx512bw\")) return 3;
     if (!__builtin_cpu_supports(\"avx512vl\")) return 4;
     __m512 a = _mm512_set1_ps(1.0f);
     __m512 b = _mm512_set1_ps(2.0f);
     __mmask16 m = _mm512_cmp_ps_mask(a, b, _CMP_LT_OQ);
     return m == 0xFFFF ? 0 : 5;
   }"
  WBHF_MODEM_HOST_RUNS_REQUIRED_AVX512)
unset(CMAKE_REQUIRED_FLAGS)

if(NOT WBHF_MODEM_HOST_RUNS_REQUIRED_AVX512)
  message(FATAL_ERROR "wbhf_modem requires a build host that can execute AVX-512F/DQ/BW/VL.")
endif()

target_sources(wbhf_modem PRIVATE src/demapper_avx512.cpp)
target_compile_options(wbhf_modem PRIVATE -march=native)
target_compile_definitions(wbhf_modem PRIVATE WBHF_MODEM_COMPILED_AVX512=1)

if(EXISTS "/proc/cpuinfo")
  file(READ "/proc/cpuinfo" WBHF_MODEM_CPUINFO)
  string(TOLOWER "${WBHF_MODEM_CPUINFO}" WBHF_MODEM_CPUINFO_LOWER)
  foreach(feature IN ITEMS
      avx512f avx512dq avx512ifma avx512cd avx512bw avx512vl
      avx512vbmi avx512_vbmi2 avx512_vnni avx512_bitalg
      avx512_vpopcntdq avx512_vp2intersect vaes vpclmulqdq gfni)
    string(TOUPPER "${feature}" feature_upper)
    if(WBHF_MODEM_CPUINFO_LOWER MATCHES "(^|[ \n])${feature}($|[ \n])")
      target_compile_definitions(wbhf_modem PRIVATE "WBHF_MODEM_HOST_${feature_upper}=1")
    endif()
  endforeach()
endif()

message(STATUS "wbhf_modem: compiling DSP with -march=native and mandatory AVX-512F/DQ/BW/VL")

if(MSVC)
  target_compile_options(wbhf_modem PRIVATE /W4 /permissive-)
else()
  target_compile_options(wbhf_modem PRIVATE -Wall -Wextra -Wpedantic)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(wbhf_modem PRIVATE -Wno-psabi)
  endif()
endif()

if(WBHF_MODEM_BUILD_EXAMPLES)
  add_executable(wbhf_stream_loopback examples/stream_loopback.cpp)
  target_link_libraries(wbhf_stream_loopback PRIVATE wbhf_modem::wbhf_modem)
  add_executable(wbhf_local_node examples/local_node.cpp)
  target_link_libraries(wbhf_local_node PRIVATE wbhf_modem::wbhf_modem)
  add_executable(wbhf_radio_sender examples/radio_sender.cpp)
  target_link_libraries(wbhf_radio_sender PRIVATE wbhf_modem::wbhf_modem)
  add_executable(wbhf_radio_receiver examples/radio_receiver.cpp)
  target_link_libraries(wbhf_radio_receiver PRIVATE wbhf_modem::wbhf_modem)
  target_include_directories(wbhf_radio_receiver PRIVATE "${WBHF_MODEM_GENERATED_DIR}")
endif()

if(WBHF_MODEM_BUILD_TESTS)
  include(CTest)
  if(BUILD_TESTING)
    add_executable(wbhf_modem_tests tests/test_modem.cpp)
    target_link_libraries(wbhf_modem_tests PRIVATE wbhf_modem::wbhf_modem)
    target_include_directories(wbhf_modem_tests PRIVATE "${WBHF_MODEM_GENERATED_DIR}")
    add_test(NAME wbhf_modem_tests COMMAND wbhf_modem_tests)
  endif()
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  TARGETS wbhf_modem
  EXPORT wbhf_modemTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY proto/ DESTINATION ${CMAKE_INSTALL_DATADIR}/wbhf_modem/proto)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/wbhf_modemConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  cmake/wbhf_modemConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/wbhf_modemConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/wbhf_modem)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/wbhf_modemConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/wbhf_modemConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/wbhf_modem)

install(
  EXPORT wbhf_modemTargets
  NAMESPACE wbhf_modem::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/wbhf_modem)
