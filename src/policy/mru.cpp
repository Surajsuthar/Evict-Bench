#include "evict-benchmark/policy/mru.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <stdexcept>

namespace evictbench {

MRUPolicy::MRUPolicy(std::size_t capacity)
    : EvictionPolicy(capacity), _capacity(capacity) {
  if (capacity == 0) {
    throw std::invalid_argument("MRU capacity must be > 0");
  }
}

bool MRUPolicy::Access(PageId page_id) {

  if (table_.contains(page_id)) {
    auto it = table_.find(page_id);
    list_.erase(it->second);
    list_.push_front(it->first);
    table_[page_id] = list_.begin();

    return true;
  }

  if (table_.size() >= _capacity) {
    // evit
    Evict();
  }

  list_.push_front(page_id);
  table_[page_id] = list_.begin();
  return false;
}

std::optional<PageId> MRUPolicy::Evict() {
  if (list_.empty())
    return std::nullopt;

  PageId victicm = list_.front();
  list_.pop_front();
  table_.erase(victicm);
  return victicm;
}

bool MRUPolicy::Contains(PageId page_id) {
  auto it = table_.contains(page_id);
  return it;
}

bool MRUPolicy::Remove(PageId page_id) {
  auto it = table_.find(page_id);
  if (it == table_.end()) {
    return false;
  }
  list_.erase(it->second);
  table_.erase(it);
  return true;
}

std::size_t MRUPolicy::Size() const { return table_.size(); }

void MRUPolicy::Clear() {
  table_.clear();
  list_.clear();
}
} // namespace evictbench
