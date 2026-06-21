#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>

namespace evictbench {

class LFUPolicy : public EvictionPolicy {
public:
  explicit LFUPolicy(std::size_t capacity);
  bool Access(PageId page_id) override;
  std::optional<PageId> Evict() override;

  bool Contains(PageId page_id) override;
  bool Remove(PageId page_id) override;
  std::size_t Size() const override;
  void Clear() override;

private:
  struct PageInfo {
    std::size_t freq;
    std::list<PageId>::iterator position;
  };

  std::size_t capacity_;
  std::size_t min_freq_;
  using ListIt = std::list<PageId>::iterator;
  std::unordered_map<std::size_t, std::list<PageId>> freq_list_;
  std::unordered_map<PageId, PageInfo> pages_;
};
} // namespace evictbench
