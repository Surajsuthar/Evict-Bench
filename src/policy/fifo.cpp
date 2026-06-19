
#include "evict-benchmark/policy/fifo.h"
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <type_traits>

namespace evictbench {

FIFOPolicy::FIFOPolicy(std::size_t capacity) : EvictionPolicy(capacity) {
  if (capacity == 0)
    throw std::invalid_argument("FIFO capacity must be > 0");
}

bool FIFOPolicy::Access(PageId page_id) {
  if (_table.contains(page_id)) {
    return true;
  }
  if (_table.size() >= capacity) {
    // evit;
  }
  _queue.push(page_id);
  _table.insert(page_id);
  return false;
}

std::optional<PageId> FIFOPolicy::Evict() {
  if (_queue.empty())
    return std::nullopt;

  PageId evictim = _queue.front();
  _queue.pop();
  _table.erase(evictim);

  return evictim;
}

bool FIFOPolicy::Contains(PageId page_id) { return _table.contains(page_id); }

std::size_t FIFOPolicy::Size() const { return _table.size(); }

void FIFOPolicy::Clear() { _table.clear(); }

} // namespace evictbench
