#pragma once

#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <queue>
#include <unordered_set>

namespace evictbench {

class FIFOPolicy : public EvictionPolicy {
public:
  explicit FIFOPolicy(std::size_t capacity);
  bool Access(PageId page_id) override;
  std::optional<PageId> Evict() override;

  bool Contains(PageId page_id) override;
  bool Remove(PageId page_id) override;
  std::size_t Size() const override;
  void Clear() override;

private:
  std::queue<PageId> _queue;
  std::unordered_set<PageId> _table;
};
} // namespace evictbench
