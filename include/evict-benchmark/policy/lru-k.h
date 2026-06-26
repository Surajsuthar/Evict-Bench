#pragma once

#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>

namespace evictbench {

class LRUKPolicy : public EvictionPolicy {
public:
  explicit LRUKPolicy(std::size_t capacity, std::size_t k);
  bool Access(PageId page_id) override;
  std::optional<PageId> Evict() override;

  bool Contains(PageId page_id) override;
  bool Remove(PageId page_id) override;
  std::size_t Size() const override;
  void Clear() override;

private:
  std::size_t capacity_;
  std::size_t k_;
  std::size_t clock_{0};
  std::unordered_map<PageId, std::list<size_t>> table_;
};
} // namespace evictbench
