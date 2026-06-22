#include "evict-benchmark/policy/lfu.h"

#include <gtest/gtest.h>

namespace evictbench {

TEST(LFUPolicyTest, FirstAccessIsMiss) {
  LFUPolicy lfu(3);

  const bool hit = lfu.Access(10);

  EXPECT_FALSE(hit);
  EXPECT_TRUE(lfu.Contains(10));
  EXPECT_EQ(lfu.Size(), 1);
}

TEST(LFUPolicyTest, SecondAccessIsHit) {
  LFUPolicy lfu(3);

  lfu.Access(10);
  const bool hit = lfu.Access(10);

  EXPECT_TRUE(hit);
  EXPECT_EQ(lfu.Size(), 1);
}

TEST(LFUPolicyTest, EvictsOldestPage) {
  LFUPolicy lfu(3);
  lfu.Access(10);
  lfu.Access(20);
  lfu.Access(30);

  const auto victim = lfu.Evict();

  ASSERT_TRUE(victim.has_value());
  EXPECT_EQ(*victim, 10);
  EXPECT_FALSE(lfu.Contains(10));
}

TEST(LFUPolicyTest, HitDoesNotChangeOrder) {
  LFUPolicy lfu(3);
  lfu.Access(10);
  lfu.Access(20);

  EXPECT_TRUE(lfu.Access(10));
  EXPECT_EQ(lfu.Evict(), 10);
}

} // namespace evictbench
