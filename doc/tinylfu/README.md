# TinyLFU Eviction And Admission Policy

TinyLFU is primarily an admission policy, not a complete eviction policy by
itself. It uses a compact approximate frequency sketch to decide whether an
incoming page is worth admitting over an existing eviction candidate.

## Core Idea

- Maintain approximate recent access frequencies in a compact sketch.
- Let a backing eviction policy, often segmented LRU, choose a candidate victim.
- On miss when full, compare the estimated frequency of the incoming page with
  the victim's estimated frequency.
- Admit the incoming page only if it is likely to be more valuable.
- Periodically age the sketch so old popularity fades.

W-TinyLFU combines a small LRU window, a probation segment, a protected segment,
and TinyLFU admission.

## Metadata

- Count-min sketch or similar approximate frequency structure.
- Doorkeeper Bloom filter in some variants.
- Backing cache metadata, commonly window/probation/protected LRU lists.
- Aging epoch or sample counter.

## Expected Behavior

TinyLFU is strong when many one-hit pages compete with a stable popular set. It
is especially useful for web, key-value, and database traces with skew. Because
it is admission-oriented, benchmark reports should state the backing eviction
policy used with it.

For this benchmark, TinyLFU should be expected to:

- reject scan pollution better than pure LRU;
- work well on Zipfian and hot/cold workloads;
- adapt according to the sketch aging window and protected/probation sizing.

## Paper Trail

- Gil Einziger, Roy Friedman, and Ben Manes, "TinyLFU: A Highly Efficient Cache
  Admission Policy", 2015. https://arxiv.org/abs/1512.00727
- Gil Einziger, Ohad Eytan, Roy Friedman, and Benjamin Manes, "Lightweight
  Robust Size Aware Cache Management", 2021. https://arxiv.org/abs/2105.08770
