cmake_minimum_required(VERSION 3.10)

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
