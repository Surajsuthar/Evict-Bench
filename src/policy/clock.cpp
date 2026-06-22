#include "evict-benchmark/policy/clock.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>

namespace evictbench {
ClockPolicy::ClockPolicy(std::size_t capacity)
    : EvictionPolicy(capacity), _capacity(capacity) {
  if (capacity == 0) {
    throw std::invalid_argument("Capacity must be greater than 0");
  }
}

bool ClockPolicy::Access(PageId page) {}

std::optional<PageId> ClockPolicy::Evict() {}

bool ClockPolicy::Contains(PageId page) {}

bool ClockPolicy::Remove(PageId page) {}

std::size_t ClockPolicy::Size() const {}

void ClockPolicy::Clear() {}

} // namespace evictbench
