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
  message(FATAL_ERROR "wbhf_modem requires an x86_64 host build.")
endif()

# Core library baseline: AVX (Sandy Bridge, 2012). This is the minimum the
# *transmitter* needs and lets the same binary run on a Dell R820 (Xeon
# E5-4600 v1/v2). The receiver binary lifts its own baseline to AVX2 + FMA.
# The demapper kernels are compiled at higher ISAs in their own TUs and
# selected at runtime by detail::pick_isa.
check_cxx_compiler_flag("-mavx" WBHF_MODEM_COMPILER_HAS_AVX)
if(NOT WBHF_MODEM_COMPILER_HAS_AVX)
  message(FATAL_ERROR "wbhf_modem requires compiler support for -mavx.")
endif()
check_cxx_compiler_flag("-mavx2 -mfma" WBHF_MODEM_COMPILER_HAS_AVX2_FMA)
if(NOT WBHF_MODEM_COMPILER_HAS_AVX2_FMA)
  message(FATAL_ERROR "wbhf_modem requires compiler support for -mavx2 -mfma.")
endif()
check_cxx_compiler_flag("-mavx512f -mavx512dq -mavx512bw -mavx512vl"
                         WBHF_MODEM_COMPILER_HAS_AVX512)
if(NOT WBHF_MODEM_COMPILER_HAS_AVX512)
  message(FATAL_ERROR "wbhf_modem requires compiler support for AVX-512 codegen "
                      "(the actual ISA is selected at runtime).")
endif()

target_sources(wbhf_modem PRIVATE src/demapper_avx2.cpp src/demapper_avx512.cpp)

# Library baseline -mavx -- works on R820 (Sandy Bridge-EP / Ivy Bridge-EP).
target_compile_options(wbhf_modem PRIVATE -mavx)

# Per-TU upgrades for the SIMD demappers. These objects only get *called*
# when the runtime CPU supports them; building them at higher ISAs is safe
# because no code path reaches them otherwise.
set_source_files_properties(src/demapper_avx2.cpp
  PROPERTIES COMPILE_OPTIONS "-mavx2;-mfma")
set_source_files_properties(src/demapper_avx512.cpp
  PROPERTIES COMPILE_OPTIONS "-mavx512f;-mavx512dq;-mavx512bw;-mavx512vl")

target_compile_definitions(wbhf_modem PRIVATE
  WBHF_MODEM_COMPILED_AVX=1
  WBHF_MODEM_COMPILED_AVX2=1
  WBHF_MODEM_COMPILED_AVX512=1)

message(STATUS "wbhf_modem: library baseline -mavx, runtime dispatch to AVX2/AVX-512 demappers")

if(MSVC)
  target_compile_options(wbhf_modem PRIVATE /W4 /permissive-)
else()
  target_compile_options(wbhf_modem PRIVATE -Wall -Wextra -Wpedantic)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(wbhf_modem PRIVATE -Wno-psabi)
  endif()
endif()

if(WBHF_MODEM_BUILD_EXAMPLES)
  # Transmitter, loopback, and local node only need the AVX baseline of the
  # library; they don't exercise the SIMD demappers.
  add_executable(wbhf_stream_loopback examples/stream_loopback.cpp)
  target_link_libraries(wbhf_stream_loopback PRIVATE wbhf_modem::wbhf_modem)
  target_compile_options(wbhf_stream_loopback PRIVATE -mavx)
  add_executable(wbhf_local_node examples/local_node.cpp)
  target_link_libraries(wbhf_local_node PRIVATE wbhf_modem::wbhf_modem)
  target_compile_options(wbhf_local_node PRIVATE -mavx)
  add_executable(wbhf_radio_sender examples/radio_sender.cpp)
  target_link_libraries(wbhf_radio_sender PRIVATE wbhf_modem::wbhf_modem)
  target_compile_options(wbhf_radio_sender PRIVATE -mavx)

  # The receiver binary lifts its baseline to AVX2 + FMA so its own code
  # (and the demapper kernels it actually calls) can target AVX2 directly.
  # It still runtime-dispatches to AVX-512 when the host supports it.
  add_executable(wbhf_radio_receiver examples/radio_receiver.cpp)
  target_link_libraries(wbhf_radio_receiver PRIVATE wbhf_modem::wbhf_modem)
  target_include_directories(wbhf_radio_receiver PRIVATE "${WBHF_MODEM_GENERATED_DIR}")
  target_compile_options(wbhf_radio_receiver PRIVATE -mavx2 -mfma)
endif()

if(WBHF_MODEM_BUILD_TESTS)
  include(CTest)
  if(BUILD_TESTING)
    add_executable(wbhf_modem_tests tests/test_modem.cpp)
    target_link_libraries(wbhf_modem_tests PRIVATE wbhf_modem::wbhf_modem)
    target_include_directories(wbhf_modem_tests PRIVATE "${WBHF_MODEM_GENERATED_DIR}")
    # Tests exercise the receive path; require AVX2 baseline like the receiver.
    target_compile_options(wbhf_modem_tests PRIVATE -mavx2 -mfma)
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
