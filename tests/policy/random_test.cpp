#include "evict-benchmark/policy/fifo.h"

#include <gtest/gtest.h>

namespace evictbench {

TEST(FIFOPolicyTest, FirstAccessIsMiss) {
  FIFOPolicy fifo(3);

  const bool hit = fifo.Access(10);

  EXPECT_FALSE(hit);
  EXPECT_TRUE(fifo.Contains(10));
  EXPECT_EQ(fifo.Size(), 1);
}

TEST(FIFOPolicyTest, SecondAccessIsHit) {
  FIFOPolicy fifo(3);

  fifo.Access(10);
  const bool hit = fifo.Access(10);

  EXPECT_TRUE(hit);
  EXPECT_EQ(fifo.Size(), 1);
}

TEST(FIFOPolicyTest, EvictsOldestPage) {
  FIFOPolicy fifo(3);
  fifo.Access(10);
  fifo.Access(20);
  fifo.Access(30);

  const auto victim = fifo.Evict();

  ASSERT_TRUE(victim.has_value());
  EXPECT_EQ(*victim, 10);
  EXPECT_FALSE(fifo.Contains(10));
}

TEST(FIFOPolicyTest, HitDoesNotChangeOrder) {
  FIFOPolicy fifo(3);
  fifo.Access(10);
  fifo.Access(20);

  EXPECT_TRUE(fifo.Access(10));
  EXPECT_EQ(fifo.Evict(), 10);
}

} // namespace evictbench
