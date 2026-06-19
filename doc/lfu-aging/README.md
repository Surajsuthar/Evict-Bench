# LFU-Aging Eviction Policy

LFU-Aging keeps the frequency idea from LFU but periodically reduces or expires
old counts. This prevents pages that were popular in an earlier workload phase
from remaining protected forever.

## Core Idea

- Track frequency counters like LFU.
- Apply aging at fixed intervals, on global epoch changes, or during eviction.
- Common aging choices are halving counters, subtracting a global minimum, or
  keeping counts in a sliding time window.
- Evict the page with the lowest aged frequency, using recency as a tie-breaker.

## Metadata

- Page id to counter.
- Last aging epoch or global aging state.
- Frequency buckets, heap, or ordered set.
- Optional recency order for tie-breaking.

## Expected Behavior

LFU-Aging is better than plain LFU when popularity changes over time. The aging
rate is the key tradeoff: aggressive aging behaves closer to LRU, while slow
aging behaves closer to LFU.

For this benchmark, LFU-Aging should be expected to:

- improve LFU on bursty and phase-changing traces;
- retain LFU's strength on stable skew if aging is not too aggressive;
- expose sensitivity to the chosen aging interval.

## Paper Trail

- Wolfgang Effelsberg and Theo Haerder, "Principles of Database Buffer
  Management", ACM TODS, 1984. DOI: https://doi.org/10.1145/357775.357784
- Gil Einziger, Roy Friedman, and Ben Manes, "TinyLFU: A Highly Efficient Cache
  Admission Policy", 2015. https://arxiv.org/abs/1512.00727
