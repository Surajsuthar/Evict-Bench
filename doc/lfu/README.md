# LFU Eviction Policy

LFU, or least frequently used, evicts the resident page with the smallest access
count. It favors pages that have accumulated repeated use over time.

## Core Idea

- Maintain an access count for each resident page.
- On hit, increment the page count.
- On miss, insert with an initial count, usually `1`.
- On eviction, choose the resident page with the lowest count.
- Use recency as a deterministic tie-breaker so old low-count pages leave first.

## Metadata

- Page id to frequency counter.
- Frequency buckets, heap, or ordered set for victim selection.
- Optional recency order within each frequency.

An O(1) LFU implementation uses frequency buckets and per-frequency linked
lists. Simpler benchmark implementations can start with a heap or ordered set.

## Expected Behavior

LFU works well on skewed workloads where historical popularity is stable. Its
main weakness is stale popularity: a page that was hot early can remain protected
long after the workload shifts. Aging or windowed counting is normally needed in
long-running systems.

For this benchmark, LFU should be expected to:

- do well on stable Zipfian and hot/cold traces;
- react slowly to phase changes and bursts;
- motivate LFU-Aging and TinyLFU as more practical variants.

## Paper Trail

- Ketan Shah, Anirban Mitra, and Dhruv Matani, "An O(1) Algorithm for
  Implementing the LFU Cache Eviction Scheme", 2010/2021 preprint.
  https://arxiv.org/abs/2110.11602
- Wolfgang Effelsberg and Theo Haerder, "Principles of Database Buffer
  Management", ACM TODS, 1984. DOI: https://doi.org/10.1145/357775.357784
