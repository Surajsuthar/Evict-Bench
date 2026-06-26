#include "evict-benchmark/policy/arc.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <utility>

namespace evictbench {

ARCPolicy::ARCPolicy(std::size_t capacity)
    : EvictionPolicy(capacity), capacity_(capacity), target_mru_size_(0),
      curr_size_(0) {}

bool ARCPolicy::Access(PageId page_id) {
  auto alive_it = cached_table_.find(page_id);
  if (alive_it != cached_table_.end()) {
  }

  auto ghost_it = cached_table_.find(page_id);
  if (ghost_it != ghost_table_.end()) {
  }

  // ecit
  // new enties
}

std::optional<PageId> ARCPolicy::Evict() {}

bool ARCPolicy::Contains(PageId page_id) {}

bool ARCPolicy::Remove(PageId page_id) {}

std::size_t ARCPolicy::Size() const { return curr_size_; }

void ARCPolicy::Clear() {
  cached_table_.clear();
  ghost_table_.clear();
  mru_.clear();
  mfu_.clear();
  ghost_mru_.clear();
  ghost_mfu_.clear();
  curr_size_ = 0;
}

} // namespace evictbench
