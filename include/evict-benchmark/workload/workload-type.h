#pragma once

#include "evict-benchmark/comman/type.h"
#include <cstdint>
#include <string>
namespace evictbench {}

namespace evictbench {

struct WorkloadTypeInfo {
  PageId page_id;
  TimeStamp timestamps;
};

enum class WorkloadType {
  ZIPF,
  UNIFORM,
  SEQUENTIAL,
  OLTP,
  CYCLIC,
};

inline std::string to_string(WorkloadType type) {
  switch (type) {
  case WorkloadType::ZIPF:
    return "ZipfWorkload";
  case WorkloadType::UNIFORM:
    return "UniformWorkload";
  case WorkloadType::SEQUENTIAL:
    return "SequentialWorkload";
  case WorkloadType::OLTP:
    return "OltpWorkload";
  case WorkloadType::CYCLIC:
    return "CyclicWorkload";
  default:
    return "UnknownWorkload";
  }
}
} // namespace evictbench
