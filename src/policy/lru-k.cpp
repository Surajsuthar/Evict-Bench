#include "evict-benchmark/policy/lru-k.h"

#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"

#include <cstddef>
#include <optional>
#include <stdexcept>

namespace evictbench {

LRUKPolicy::LRUKPolicy(std::size_t capacity, std::size_t k)
    : EvictionPolicy(capacity), capacity_(capacity), k_(k), clock_(0) {
  if (capacity == 0) {
    throw std::invalid_argument("LRU-K capacity must be > 0");
  }

  if (k == 0) {
    throw std::invalid_argument("LRU-K value must be > 0");
  }
}

bool LRUKPolicy::Access(PageId page_id) {
  ++clock_;

  auto it = table_.find(page_id);

  // Cache hit.
  if (it != table_.end()) {
    auto &history = it->second;

    history.push_back(clock_);

    // Keep only the most recent K timestamps.
    while (history.size() > k_) {
      history.pop_front();
    }

    return true;
  }

  // Cache miss: make room if necessary.
  if (table_.size() >= capacity_) {
    Evict();
  }

  table_[page_id].push_back(clock_);
  return false;
}

std::optional<PageId> LRUKPolicy::Evict() {
  if (table_.empty()) {
    return std::nullopt;
  }

  auto victim = table_.end();

  // First pass:
  // Prefer pages with fewer than K accesses.
  for (auto it = table_.begin(); it != table_.end(); ++it) {
    const auto &history = it->second;

    if (history.size() >= k_) {
      continue;
    }

    // First candidate with < K accesses.
    if (victim == table_.end()) {
      victim = it;
      continue;
    }

    const auto &victim_history = victim->second;

    // Among pages with < K accesses, evict one whose latest access is oldest.
    if (history.back() < victim_history.back()) {
      victim = it;
    }
  }

  // If no page has fewer than K accesses,
  // choose page whose K-th most recent access is oldest.
  if (victim == table_.end()) {
    for (auto it = table_.begin(); it != table_.end(); ++it) {
      if (victim == table_.end()) {
        victim = it;
        continue;
      }

      // Since each history keeps at most K timestamps,
      // front() is the K-th most recent timestamp.
      if (it->second.front() < victim->second.front()) {
        victim = it;
      }
    }
  }

  PageId victim_page_id = victim->first;
  table_.erase(victim);

  return victim_page_id;
}

bool LRUKPolicy::Contains(PageId page_id) { return table_.contains(page_id); }

bool LRUKPolicy::Remove(PageId page_id) {
  auto it = table_.find(page_id);

  if (it == table_.end()) {
    return false;
  }

  table_.erase(it);
  return true;
}

std::size_t LRUKPolicy::Size() const { return table_.size(); }

void LRUKPolicy::Clear() {
  table_.clear();
  clock_ = 0;
}

} // namespace evictbench
