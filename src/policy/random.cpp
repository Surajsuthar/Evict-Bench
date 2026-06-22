#include "evict-benchmark/policy/random.h"
#include "evict-benchmark/policy/evict-policy.h"
#include <cstddef>
#include <random>
#include <utility>
namespace evictbench {

RandomPolicy::RandomPolicy(std::size_t capacity)
    : EvictionPolicy(capacity), capacity_(capacity) {
  if (capacity == 0) {
    throw std::invalid_argument("Random capacity must be > 0");
  }
}

bool RandomPolicy::Access(PageId page_id) {
  auto it = table_.find(page_id);
  if (it != table_.end()) {
    std::size_t idx = it->second;
    return pages_[idx];
  }

  if (pages_.size() >= capacity_) {
    Evict();
  }

  pages_.push_back(page_id);
}

std::optional<PageId> RandomPolicy::Evict() {
  if (!Size()) {
    return std::nullopt;
  }
  int idx = random_();
  std::size_t size = Size();
  std::swap(pages_[idx], pages_[size - 1]);
  int victim = pages_[idx];
  return victim;
}

bool RandomPolicy::Contains(PageId page_id) { return table_.contains(page_id); }

bool RandomPolicy::Remove(PageId page_id) {
  auto it = table_.find(page_id);
  if (it != table_.end()) {
    std::size_t idx = table_[page_id];
    std::swap(pages_[Size() - 1], pages_[idx]);
    pages_.pop_back();
  }
}

int RandomPolicy::random_() {
  std::size_t size = Size();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, size - 1);
  int random_num = dist(gen);

  return random_num;
}

std::size_t RandomPolicy::Size() const { return pages_.size(); }

void RandomPolicy::Clear() { pages_.clear(); }

} // namespace evictbench
