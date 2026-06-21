
#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <optional>
#include <unordered_map>
#include <vector>

namespace evictbench {

class RandomPolicy : public EvictionPolicy {
public:
  explicit RandomPolicy(std::size_t capacity);
  bool Access(evictbench::PageId page_id) override;
  std::optional<PageId> Evict() override;

  bool Contains(PageId page_id) override;
  bool Remove(PageId page_id) override;
  std::size_t Size() const override;
  void Clear() override;

private:
  int random_();

  std::size_t capacity_;
  std::vector<PageId> pages_;
  std::unordered_map<PageId, std::size_t> table_;
};
} // namespace evictbench
