#include "evict-benchmark/policy/clock.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <utility>

namespace evictbench {
ClockPolicy::ClockPolicy(std::size_t capacity)
    : EvictionPolicy(capacity), capacity_(capacity), clock_hand_(0) {
  if (capacity == 0) {
    throw std::invalid_argument("Capacity must be greater than 0");
  }

  pages_.resize(capacity);
}

bool ClockPolicy::Access(PageId page_id) {
  auto it = table_.find(page_id);
  if (it != table_.end()) {
    std::size_t index = it->second;
    pages_[index].reference_bit = true;
    return true;
  }

  if (size_ == capacity_) {
    Evict();
  }

  while (pages_[clock_hand_].occupied) {
    clock_hand_ = (clock_hand_ + 1) % capacity_;
  }

  pages_[clock_hand_] = Slot{page_id, true, true};
  table_[page_id] = clock_hand_;
  ++size_;
  clock_hand_ = (clock_hand_ + 1) % capacity_;
  return false;
}

std::optional<PageId> ClockPolicy::Evict() {
  if (size_ == 0)
    return std::nullopt;
  while (true) {
    Slot &slot = pages_[clock_hand_];

    // Removed/empty slots are skipped.
    if (!slot.occupied) {
      clock_hand_ = (clock_hand_ + 1) % capacity_;
      continue;
    }

    // Recently used page: give it a second chance.
    if (slot.reference_bit) {
      slot.reference_bit = false;
      clock_hand_ = (clock_hand_ + 1) % capacity_;
      continue;
    }

    // Found victim: occupied and reference bit is 0.
    const PageId victim = slot.page_id;

    table_.erase(victim);

    slot.occupied = false;
    slot.reference_bit = false;

    --size_;

    // Keep the hand at the next position.
    clock_hand_ = (clock_hand_ + 1) % capacity_;

    return victim;
  }
}

bool ClockPolicy::Contains(PageId page_id) { return table_.contains(page_id); }

bool ClockPolicy::Remove(PageId page_id) {
  auto it = table_.find(page_id);

  if (it == table_.end()) {
    return false;
  }

  const std::size_t index = it->second;

  pages_[index].occupied = false;
  pages_[index].reference_bit = false;

  table_.erase(it);
  --size_;

  return true;
}

std::size_t ClockPolicy::Size() const { return size_; }

void ClockPolicy::Clear() {
  table_.clear();

  for (Slot &slot : pages_) {
    slot.occupied = false;
    slot.reference_bit = false;
  }

  size_ = 0;
  clock_hand_ = 0;
}

} // namespace evictbench
