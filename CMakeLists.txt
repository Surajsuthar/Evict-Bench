cmake_minimum_required(VERSION 3.14)

project("evict-benchmark")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(dbcache_bench
  src/main.cpp
  src/policy/fifo.cpp
  src/policy/opt.cpp
  src/simulator/simulator.cpp
  src/workloads/workload.cpp
)

target_compile_features(dbcache_bench PRIVATE cxx_std_20)
target_include_directories(dbcache_bench PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(CTest)

if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  FetchContent_MakeAvailable(googletest)

  add_executable(policy_tests
    tests/policy/fifo_test.cpp
    src/policy/fifo.cpp
  )
  target_compile_features(policy_tests PRIVATE cxx_std_20)
  target_include_directories(policy_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(policy_tests PRIVATE GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(policy_tests)
endif()
