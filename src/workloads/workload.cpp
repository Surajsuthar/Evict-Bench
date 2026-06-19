#include "evict-benchmark/workload/workload.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/workload/workload-type.h"
#include <cstdint>
#include <vector>

namespace evictbench {

std::vector<WorkloadTypeInfo> WorkLoad::ZipfWorkload(std::size_t length) {
  std::vector<WorkloadTypeInfo> out;

  return out;
}

std::vector<WorkloadTypeInfo> WorkLoad::UniformWorkload(std::size_t length) {
  std::vector<WorkloadTypeInfo> out;
  return out;
}

std::vector<WorkloadTypeInfo> WorkLoad::SequentialWorkload(std::size_t length) {
  std::vector<WorkloadTypeInfo> out;

  for (std::size_t i = 1; i <= length; i++) {
    out.push_back({.page_id = static_cast<PageId>(i),
                   .timestamps = static_cast<TimeStamp>(i)});
  }

  return out;
}

std::vector<WorkloadTypeInfo> WorkLoad::OLTPWorkload(std::size_t length) {
  std::vector<WorkloadTypeInfo> out;
  return out;
}

std::vector<WorkloadTypeInfo> WorkLoad::CyclicWorkload(std::size_t length,
                                                       size_t cycle_size) {
  std::vector<WorkloadTypeInfo> out;

  for (std::size_t i = 1; i <= length; i++) {
    out.push_back({.page_id = static_cast<PageId>(i % cycle_size),
                   .timestamps = static_cast<TimeStamp>(i)});
  }

  return out;
}

std::vector<WorkloadTypeInfo> WorkLoad::HotColdLoad(std::size_t length,
                                                    std::size_t hot_size) {
  std::vector<WorkloadTypeInfo> out;

  return out;
}

std::vector<WorkloadTypeInfo> WorkLoad::BurstyWorkload(std::size_t length,
                                                       std::size_t phase_length,
                                                       PageId pages_per_phase) {
  std::vector<WorkloadTypeInfo> out;
  return out;
}

} // namespace evictbench

// class Workload {
// public:
//   virtual std::vector<uint64_t> generate() = 0;
// };

// class ZipfWorkload : public Workload {
// public:
//   std::vector<uint64_t> generate() override {
//     std::vector<uint64_t> result;

//     return result;
//   }
// };

// class UniformWorkload : public Workload {
// public:
//   std::vector<uint64_t> generate() override {
//     std::vector<uint64_t> result;

//     return result;
//   }
// };

// class SequentialWorkload : public Workload {
// public:
//   std::vector<uint64_t> generate() override {
//     std::vector<uint64_t> result;

//     return result;
//   }
// };

// class OltpWorkload : public Workload {
// public:
//   std::vector<uint64_t> generate() override {
//     std::vector<uint64_t> result;

//     return result;
//   }
// };

// class CyclicWorkload : public Workload {
// public:
//   std::vector<uint64_t> generate() override {
//     std::vector<uint64_t> result;

//     return result;
//   }
// };
