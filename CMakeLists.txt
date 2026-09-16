cmake_minimum_required(VERSION 3.24)

project(
  goblin_cannon
  VERSION 0.1.0
  DESCRIPTION "Goblin Cannon low-latency HF market-data radio stack"
  LANGUAGES CXX)

option(GOBLIN_CANNON_BUILD_EXAMPLES "Build example programs" ON)
option(GOBLIN_CANNON_BUILD_TESTS "Build tests" ON)
option(GOBLIN_CANNON_TEST_REQUIRE_AVX512 "Require AVX-512 demapper dispatch in channel tests" OFF)
option(GOBLIN_CANNON_RUN_SIMULATED_CHANNEL_QUICK "Include the complete brief's simulated channel quick tier in CTest" OFF)
set(GOBLIN_CANNON_TEST_GIT_COMMIT "" CACHE STRING "Origin commit for simulated channel reports from source copies")
add_library(goblin_cannon
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

add_library(goblin_cannon::goblin_cannon ALIAS goblin_cannon)

target_compile_features(goblin_cannon PUBLIC cxx_std_23)
target_include_directories(
  goblin_cannon
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_definitions(goblin_cannon PRIVATE GOBLIN_CANNON_VERSION="${PROJECT_VERSION}")

find_package(OpenSSL REQUIRED COMPONENTS Crypto)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_program(GOBLIN_CANNON_GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)

target_link_libraries(goblin_cannon PUBLIC OpenSSL::Crypto protobuf::libprotobuf gRPC::grpc++)

set(GOBLIN_CANNON_PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
set(GOBLIN_CANNON_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(GOBLIN_CANNON_CONTROL_PROTO "${GOBLIN_CANNON_PROTO_DIR}/goblin_cannon/control/v1/receiver_control.proto")
set(GOBLIN_CANNON_CONTROL_PROTO_SRCS
    "${GOBLIN_CANNON_GENERATED_DIR}/goblin_cannon/control/v1/receiver_control.pb.cc"
    "${GOBLIN_CANNON_GENERATED_DIR}/goblin_cannon/control/v1/receiver_control.grpc.pb.cc")
set(GOBLIN_CANNON_CONTROL_PROTO_HDRS
    "${GOBLIN_CANNON_GENERATED_DIR}/goblin_cannon/control/v1/receiver_control.pb.h"
    "${GOBLIN_CANNON_GENERATED_DIR}/goblin_cannon/control/v1/receiver_control.grpc.pb.h")

add_custom_command(
  OUTPUT ${GOBLIN_CANNON_CONTROL_PROTO_SRCS} ${GOBLIN_CANNON_CONTROL_PROTO_HDRS}
  COMMAND ${CMAKE_COMMAND} -E make_directory "${GOBLIN_CANNON_GENERATED_DIR}"
  COMMAND ${Protobuf_PROTOC_EXECUTABLE}
          --proto_path=${GOBLIN_CANNON_PROTO_DIR}
          --cpp_out=${GOBLIN_CANNON_GENERATED_DIR}
          --grpc_out=${GOBLIN_CANNON_GENERATED_DIR}
          --plugin=protoc-gen-grpc=${GOBLIN_CANNON_GRPC_CPP_PLUGIN}
          ${GOBLIN_CANNON_CONTROL_PROTO}
  DEPENDS "${GOBLIN_CANNON_CONTROL_PROTO}"
  VERBATIM)

target_sources(goblin_cannon PRIVATE ${GOBLIN_CANNON_CONTROL_PROTO_SRCS})
target_include_directories(goblin_cannon PRIVATE "${GOBLIN_CANNON_GENERATED_DIR}")

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)

if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
  message(FATAL_ERROR "goblin_cannon requires an x86_64 host build.")
endif()

# Core library baseline: AVX (Sandy Bridge, 2012). This is the minimum the
# *transmitter* needs and lets the same binary run on a Dell R820 (Xeon
# E5-4600 v1/v2). The receiver binary lifts its own baseline to AVX2 + FMA.
# The demapper kernels are compiled at higher ISAs in their own TUs and
# selected at runtime by detail::pick_isa.
check_cxx_compiler_flag("-mavx" GOBLIN_CANNON_COMPILER_HAS_AVX)
if(NOT GOBLIN_CANNON_COMPILER_HAS_AVX)
  message(FATAL_ERROR "goblin_cannon requires compiler support for -mavx.")
endif()
check_cxx_compiler_flag("-mavx2 -mfma" GOBLIN_CANNON_COMPILER_HAS_AVX2_FMA)
if(NOT GOBLIN_CANNON_COMPILER_HAS_AVX2_FMA)
  message(FATAL_ERROR "goblin_cannon requires compiler support for -mavx2 -mfma.")
endif()
check_cxx_compiler_flag("-mavx512f -mavx512dq -mavx512bw -mavx512vl"
                         GOBLIN_CANNON_COMPILER_HAS_AVX512)
if(NOT GOBLIN_CANNON_COMPILER_HAS_AVX512)
  message(FATAL_ERROR "goblin_cannon requires compiler support for AVX-512 codegen "
                      "(the actual ISA is selected at runtime).")
endif()

target_sources(goblin_cannon PRIVATE src/demapper_avx2.cpp src/demapper_avx512.cpp)

# Library baseline -mavx -- works on R820 (Sandy Bridge-EP / Ivy Bridge-EP).
target_compile_options(goblin_cannon PRIVATE -mavx)

# Per-TU upgrades for the SIMD demappers. These objects only get *called*
# when the runtime CPU supports them; building them at higher ISAs is safe
# because no code path reaches them otherwise.
set_source_files_properties(src/demapper_avx2.cpp
  PROPERTIES COMPILE_OPTIONS "-mavx2;-mfma")
set_source_files_properties(src/demapper_avx512.cpp
  PROPERTIES COMPILE_OPTIONS "-mavx512f;-mavx512dq;-mavx512bw;-mavx512vl")

target_compile_definitions(goblin_cannon PRIVATE
  GOBLIN_CANNON_COMPILED_AVX=1
  GOBLIN_CANNON_COMPILED_AVX2=1
  GOBLIN_CANNON_COMPILED_AVX512=1)

message(STATUS "goblin_cannon: library baseline -mavx, runtime dispatch to AVX2/AVX-512 demappers")

if(MSVC)
  target_compile_options(goblin_cannon PRIVATE /W4 /permissive-)
else()
  target_compile_options(goblin_cannon PRIVATE -Wall -Wextra -Wpedantic)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(goblin_cannon PRIVATE -Wno-psabi)
  endif()
endif()

if(GOBLIN_CANNON_BUILD_EXAMPLES)
  # Transmitter, loopback, and local node only need the AVX baseline of the
  # library; they don't exercise the SIMD demappers.
  add_executable(goblin_cannon_stream_loopback examples/stream_loopback.cpp)
  target_link_libraries(goblin_cannon_stream_loopback PRIVATE goblin_cannon::goblin_cannon)
  target_compile_options(goblin_cannon_stream_loopback PRIVATE -mavx)
  add_executable(goblin_cannon_local_node examples/local_node.cpp)
  target_link_libraries(goblin_cannon_local_node PRIVATE goblin_cannon::goblin_cannon)
  target_compile_options(goblin_cannon_local_node PRIVATE -mavx)
  add_executable(goblin_cannon_radio_sender examples/radio_sender.cpp)
  target_link_libraries(goblin_cannon_radio_sender PRIVATE goblin_cannon::goblin_cannon)
  target_compile_options(goblin_cannon_radio_sender PRIVATE -mavx)

  # The receiver binary lifts its baseline to AVX2 + FMA so its own code
  # (and the demapper kernels it actually calls) can target AVX2 directly.
  # It still runtime-dispatches to AVX-512 when the host supports it.
  add_executable(goblin_cannon_radio_receiver examples/radio_receiver.cpp)
  target_link_libraries(goblin_cannon_radio_receiver PRIVATE goblin_cannon::goblin_cannon)
  target_include_directories(goblin_cannon_radio_receiver PRIVATE "${GOBLIN_CANNON_GENERATED_DIR}")
  target_compile_options(goblin_cannon_radio_receiver PRIVATE -mavx2 -mfma)
endif()

if(GOBLIN_CANNON_BUILD_TESTS)
  include(CTest)
  if(BUILD_TESTING)
    add_executable(goblin_cannon_tests tests/test_modem.cpp)
    target_link_libraries(goblin_cannon_tests PRIVATE goblin_cannon::goblin_cannon)
    target_include_directories(goblin_cannon_tests PRIVATE "${GOBLIN_CANNON_GENERATED_DIR}")
    # Tests exercise the receive path; require AVX2 baseline like the receiver.
    target_compile_options(goblin_cannon_tests PRIVATE -mavx2 -mfma)
    add_test(NAME goblin_cannon_tests COMMAND goblin_cannon_tests)
    set_tests_properties(goblin_cannon_tests PROPERTIES LABELS "quick;assert;legacy")

    add_executable(goblin_cannon_channel_tests tests/test_channel.cpp)
    target_link_libraries(goblin_cannon_channel_tests PRIVATE goblin_cannon::goblin_cannon)
    target_include_directories(goblin_cannon_channel_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
    target_compile_options(goblin_cannon_channel_tests PRIVATE -mavx2 -mfma)
    add_executable(goblin_cannon_simulated_channel_probe tests/simulated_channel_probe.cpp)
    target_link_libraries(goblin_cannon_simulated_channel_probe PRIVATE goblin_cannon::goblin_cannon)
    target_include_directories(goblin_cannon_simulated_channel_probe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
    target_compile_options(goblin_cannon_simulated_channel_probe PRIVATE -mavx2 -mfma -Wall -Wextra -Wpedantic)
    set(channel_test_isa_arg)
    if(GOBLIN_CANNON_TEST_REQUIRE_AVX512)
      set(channel_test_isa_arg --require-avx512)
    endif()
    foreach(channel_test acquisition noise phase fading combined recovery equalization streaming config)
      add_test(NAME goblin_cannon_channel_${channel_test}
               COMMAND goblin_cannon_channel_tests ${channel_test} ${channel_test_isa_arg})
      set_tests_properties(goblin_cannon_channel_${channel_test}
                           PROPERTIES LABELS "channel;quick;assert;legacy" TIMEOUT 60)
    endforeach()
    foreach(channel_test sample_support profiles decision_delay transmit_chunks)
      add_test(NAME goblin_cannon_channel_${channel_test}
               COMMAND goblin_cannon_channel_tests ${channel_test} ${channel_test_isa_arg})
      set_tests_properties(goblin_cannon_channel_${channel_test}
                           PROPERTIES LABELS "channel;quick;assert;simulated_channel" TIMEOUT 60)
    endforeach()
    find_package(Python3 3.11 REQUIRED COMPONENTS Interpreter)
    add_executable(goblin_cannon_data_path_tests tests/test_data_path.cpp)
    target_link_libraries(goblin_cannon_data_path_tests PRIVATE goblin_cannon::goblin_cannon)
    add_test(NAME goblin_cannon_data_path COMMAND goblin_cannon_data_path_tests)
    set_tests_properties(goblin_cannon_data_path PROPERTIES LABELS "simulated_channel;quick;assert;D1;D3;D4;B4" TIMEOUT 60)
    add_test(NAME goblin_cannon_simulated_channel_harness
             COMMAND ${Python3_EXECUTABLE} -m unittest discover
                     -s "${CMAKE_CURRENT_SOURCE_DIR}/tests/simulated_channel" -p "test_*.py")
    set_tests_properties(goblin_cannon_simulated_channel_harness PROPERTIES LABELS "simulated_channel;quick;assert;E1")
    if(GOBLIN_CANNON_RUN_SIMULATED_CHANNEL_QUICK)
      if(NOT GOBLIN_CANNON_TEST_GIT_COMMIT)
        execute_process(COMMAND git -C "${CMAKE_CURRENT_SOURCE_DIR}" rev-parse HEAD
                        OUTPUT_VARIABLE GOBLIN_CANNON_TEST_GIT_COMMIT OUTPUT_STRIP_TRAILING_WHITESPACE)
      endif()
      if(NOT GOBLIN_CANNON_TEST_GIT_COMMIT)
        message(FATAL_ERROR "Set GOBLIN_CANNON_TEST_GIT_COMMIT for a source copy without .git")
      endif()
      add_test(NAME goblin_cannon_simulated_channel_quick
               COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/tests/simulated_channel/run.py"
                       --tier quick --probe $<TARGET_FILE:goblin_cannon_simulated_channel_probe>
                       --results "${CMAKE_CURRENT_BINARY_DIR}/simulated-channel-results"
                       --git-commit "${GOBLIN_CANNON_TEST_GIT_COMMIT}")
      set_tests_properties(goblin_cannon_simulated_channel_quick PROPERTIES LABELS "simulated_channel;quick" RUN_SERIAL TRUE)
    endif()
  endif()
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  TARGETS goblin_cannon
  EXPORT goblin_cannonTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY proto/ DESTINATION ${CMAKE_INSTALL_DATADIR}/goblin_cannon/proto)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/goblin_cannonConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  cmake/goblin_cannonConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/goblin_cannonConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/goblin_cannon)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/goblin_cannonConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/goblin_cannonConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/goblin_cannon)

install(
  EXPORT goblin_cannonTargets
  NAMESPACE goblin_cannon::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/goblin_cannon)
