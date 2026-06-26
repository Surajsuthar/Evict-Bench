#pragma once

#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>

namespace evictbench {

class ARCPolicy : public EvictionPolicy {
public:
  explicit ARCPolicy(std::size_t capacity);
  bool Access(PageId page_id) override;
  std::optional<PageId> Evict() override;

  bool Contains(PageId page_id) override;
  bool Remove(PageId page_id) override;
  std::size_t Size() const override;
  void Clear() override;

private:
  std::size_t capacity_;

  using ListIt = std::list<PageId>::iterator;
  std::list<PageId> mru_;
  std::list<PageId> mfu_;
  std::list<PageId> ghost_mru_;
  std::list<PageId> ghost_mfu_;

  std::unordered_map<PageId, ListIt> cached_table_;
  std::unordered_map<PageId, ListIt> ghost_table_;

  // adjustbale according workload
  std::size_t target_mru_size_;

  // nummber of evitable page;
  std::size_t curr_size_;
};

} // namespace evictbench
