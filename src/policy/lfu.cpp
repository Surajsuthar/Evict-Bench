#include "evict-benchmark/policy/lfu.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <stdexcept>

namespace evictbench {

LFUPolicy::LFUPolicy(std::size_t capacity)
    : EvictionPolicy(capacity), min_freq_(0), capacity_(capacity) {
  if (capacity == 0) {
    throw std::invalid_argument("LFU capacity must be > 0");
  }
}

bool LFUPolicy::Access(PageId page_id) {
  auto page_it = pages_.find(page_id);

  // Cache hit: increase frequency.
  if (page_it != pages_.end()) {
    auto &info = page_it->second;

    const std::size_t old_freq = info.freq;
    auto &old_list = freq_list_.at(old_freq);

    old_list.erase(info.position);

    if (old_list.empty()) {
      freq_list_.erase(old_freq);

      if (min_freq_ == old_freq) {
        min_freq_++;
      }
    }

    const std::size_t new_freq = old_freq + 1;
    auto &new_list = freq_list_[new_freq];

    new_list.push_back(page_id);

    info.freq = new_freq;
    info.position = std::prev(new_list.end());

    return true;
  }

  // Cache miss: make room first.
  if (pages_.size() >= capacity_) {
    Evict();
  }

  // Newly accessed page starts at frequency 1.
  auto &list = freq_list_[1];
  list.push_back(page_id);

  pages_[page_id] = PageInfo{
      .freq = 1,
      .position = std::prev(list.end()),
  };

  min_freq_ = 1;

  return false;
}

std::optional<PageId> LFUPolicy::Evict() {
  if (pages_.empty()) {
    return std::nullopt;
  }

  auto bucket_it = freq_list_.find(min_freq_);

  if (bucket_it == freq_list_.end() || bucket_it->second.empty()) {
    return std::nullopt;
  }

  auto &list = bucket_it->second;

  // Front is the least recently used page among min-frequency pages.
  PageId victim = list.front();
  list.pop_front();

  pages_.erase(victim);

  if (list.empty()) {
    freq_list_.erase(bucket_it);
  }

  // This is recalculated when a new page is inserted.
  if (pages_.empty()) {
    min_freq_ = 0;
  }

  return victim;
}

bool LFUPolicy::Contains(PageId page_id) { return pages_.contains(page_id); }

bool LFUPolicy::Remove(PageId page_id) {
  auto page_it = pages_.find(page_id);

  if (page_it == pages_.end()) {
    return false;
  }

  const std::size_t freq = page_it->second.freq;
  auto bucket_it = freq_list_.find(freq);

  if (bucket_it != freq_list_.end()) {
    bucket_it->second.erase(page_it->second.position);

    if (bucket_it->second.empty()) {
      freq_list_.erase(bucket_it);
    }
  }

  pages_.erase(page_it);

  if (pages_.empty()) {
    min_freq_ = 0;
  } else if (freq == min_freq_ &&
             freq_list_.find(min_freq_) == freq_list_.end()) {
    // Find the next smallest remaining frequency.
    min_freq_ = pages_.begin()->second.freq;

    for (const auto &[page, info] : pages_) {
      if (info.freq < min_freq_) {
        min_freq_ = info.freq;
      }
    }
  }

  return true;
}

std::size_t LFUPolicy::Size() const { return pages_.size(); }

void LFUPolicy::Clear() {
  pages_.clear();
  freq_list_.clear();
  min_freq_ = 0;
}

} // namespace evictbench
