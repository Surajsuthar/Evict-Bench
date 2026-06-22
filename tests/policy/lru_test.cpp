#include "evict-benchmark/policy/lru.h"

#include <gtest/gtest.h>

namespace evictbench {

TEST(LRUPolicyTest, FirstAccessIsMiss) {
  LRUPolicy lru(3);

  const bool hit = lru.Access(10);

  EXPECT_FALSE(hit);
  EXPECT_TRUE(lru.Contains(10));
  EXPECT_EQ(lru.Size(), 1);
}

TEST(LRUPolicyTest, SecondAccessIsHit) {
  LRUPolicy lru(3);

  lru.Access(10);
  const bool hit = lru.Access(10);

  EXPECT_TRUE(hit);
  EXPECT_EQ(lru.Size(), 1);
}

TEST(LRUPolicyTest, EvictsOldestPage) {
  LRUPolicy lru(3);
  lru.Access(10);
  lru.Access(20);
  lru.Access(30);

  const auto victim = lru.Evict();

  ASSERT_TRUE(victim.has_value());
  EXPECT_EQ(*victim, 10);
  EXPECT_FALSE(lru.Contains(10));
}

TEST(LRUPolicyTest, HitDoesNotChangeOrder) {
  LRUPolicy lru(3);
  lru.Access(10);
  lru.Access(20);

  EXPECT_TRUE(lru.Access(10));
  EXPECT_EQ(lru.Evict(), 10);
}

} // namespace evictbench
