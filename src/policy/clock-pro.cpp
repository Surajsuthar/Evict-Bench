#include "evict-benchmark/policy/clock-pro.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>

namespace evictbench {
ClockProPolicy::ClockProPolicy(std::size_t capacity)
    : EvictionPolicy(capacity), capacity_(capacity) {
  if (capacity == 0) {
    throw std::invalid_argument("Capacity must be greater than 0");
  }
}

bool ClockProPolicy::Access(PageId page_id) {}

std::optional<PageId> ClockProPolicy::Evict() {}

bool ClockProPolicy::Contains(PageId page_id) {}

bool ClockProPolicy::Remove(PageId page_id) {}

std::size_t ClockProPolicy::Size() const {}

void ClockProPolicy::Clear() {}

} // namespace evictbench
