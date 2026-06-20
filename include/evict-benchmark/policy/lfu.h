
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
  std::size_t _capacity;
  using ListIt = std::list<PageId>::iterator;
  std::list<PageId> _list;
  std::unordered_map<PageId, ListIt> _table;
};
} // namespace evictbench
