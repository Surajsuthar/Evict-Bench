#pragma once

#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>

namespace evictbench {

class LRUAgingPolicy : public EvictionPolicy {
public:
  explicit LRUAgingPolicy(std::size_t capacity);
  bool Access(PageId page_id) override;
  std::optional<PageId> Evict() override;

  bool Contains(PageId page_id) override;
  bool Remove(PageId page_id) override;
  std::size_t Size() const override;
  void Clear() override;

private:
  std::size_t capacity_;
};
} // namespace evictbench
