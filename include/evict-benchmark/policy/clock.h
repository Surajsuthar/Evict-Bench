#pragma once

#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <unordered_map>
#include <vector>

namespace evictbench {

class ClockPolicy : public EvictionPolicy {
public:
  explicit ClockPolicy(std::size_t capacity);
  bool Access(PageId page_id) override;
  std::optional<PageId> Evict() override;

  bool Contains(PageId page_id) override;
  bool Remove(PageId page_id) override;
  std::size_t Size() const override;
  void Clear() override;

private:
  struct Slot {
    PageId page_id{};
    bool reference_bit{false};
    bool occupied{false};
  };

  std::size_t capacity_;
  std::size_t size_{0};
  std::size_t clock_hand_{0};

  std::vector<Slot> pages_;
  std::unordered_map<PageId, std::size_t> table_;
};
} // namespace evictbench
