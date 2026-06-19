#pragma once

#include "evict-benchmark/comman/type.h"
#include <cstddef>
#include <cstdint>
#include <optional>

namespace evictbench {

class EvictionPolicy {
public:
  explicit EvictionPolicy(std::size_t capacity) : _capacity(capacity) {}
  virtual ~EvictionPolicy() = default;

  EvictionPolicy(const EvictionPolicy &) = delete;
  EvictionPolicy &operator=(const EvictionPolicy &) = delete;

  virtual bool Access(PageId paga_id) = 0;
  virtual std::optional<PageId> Evict() = 0;
  virtual bool Contains(PageId page_id) = 0;
  virtual bool Remove(PageId page_id) = 0;
  virtual std::size_t Size() const = 0;
  virtual void Clear() = 0;
  std::size_t Capacity() const { return _capacity; }

private:
  std::size_t _capacity;
};

} // namespace evictbench

// namespace dbcache {

// class EvictionPolicy {
// public:
//   explicit EvictionPolicy(std::size_t capacity) : capacity_(capacity) {}
//   virtual ~EvictionPolicy() = default;

//   EvictionPolicy(const EvictionPolicy &) = delete;
//   EvictionPolicy &operator=(const EvictionPolicy &) = delete;

//   [[nodiscard]] virtual std::string Name() const = 0;
//   virtual bool Access(PageId page_id, AccessType type) = 0;
//   virtual std::optional<PageId> Evict() = 0;
//   virtual bool Remove(PageId page_id) = 0;
//   [[nodiscard]] virtual bool Contains(PageId page_id) const = 0;
//   [[nodiscard]] virtual std::size_t Size() const = 0;
//   virtual void Clear() = 0;

//   [[nodiscard]] const PolicyStats &Stats() const { return stats_; }
//   [[nodiscard]] std::size_t Capacity() const { return capacity_; }

// protected:
//   std::size_t capacity_;
//   PolicyStats stats_;
// };

// } // namespace dbcache
