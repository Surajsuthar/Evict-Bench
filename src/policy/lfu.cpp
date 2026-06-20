#include "evict-benchmark/policy/lfu.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <stdexcept>

namespace evictbench {

LFUPolicy::LFUPolicy(std::size_t capacity) : EvictionPolicy(capacity) {
  if (capacity == 0) {
    throw std::invalid_argument("LRU capacity must be > 0");
  }
}

bool LFUPolicy::Access(PageId page_id) {

  if (_table.contains(page_id)) {
    auto it = _table.find(page_id);
    _list.erase(it->second);
    _list.push_front(it->first);
    _table[page_id] = _list.begin();

    return true;
  }

  if (_table.size() >= _capacity) {
    // evit
    Evict();
  }

  _list.push_front(page_id);
  _table[page_id] = _list.begin();
  return false;
}

std::optional<PageId> LFUPolicy::Evict() {
  if (_list.empty())
    return std::nullopt;

  PageId victicm = _list.back();
  _list.pop_back();
  _table.erase(victicm);
  return victicm;
}

bool LFUPolicy::Contains(PageId page_id) {
  auto it = _table.contains(page_id);
  return it;
}

bool LFUPolicy::Remove(PageId page_id) {
  auto it = _table.find(page_id);
  if (it == _table.end()) {
    return false;
  }
  _list.erase(it->second);
  _table.erase(it);
  return true;
}

std::size_t LFUPolicy::Size() const { return _table.size(); }

void LFUPolicy::Clear() {
  _table.clear();
  _list.clear();
}
} // namespace evictbench
