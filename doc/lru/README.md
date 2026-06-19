# LRU Eviction Policy

LRU, or least recently used, evicts the resident page whose last access is
oldest. It is based on temporal locality: recently used pages are more likely to
be used again soon.

## Core Idea

- Keep resident pages ordered from most recently used to least recently used.
- On hit, move the page to the most-recent position.
- On miss, insert the page as most recent.
- On eviction, remove the least-recent page.

## Metadata

- Doubly linked recency list.
- Page id to list node map.

This gives O(1) hit, insert, remove, and evict in a software cache.

## Expected Behavior

LRU is a strong general baseline for workloads with stable temporal locality.
Its main weakness is scan pollution: a large one-time scan can push hot pages out
of the cache. It can also fail badly on cyclic scans whose working set is just
larger than cache capacity.

For this benchmark, LRU should be expected to:

- do well on hot/cold and Zipfian traces;
- perform poorly on large sequential scans mixed with a small hot set;
- serve as the reference point for scan-resistant policies such as 2Q, ARC,
  LIRS, CLOCK-Pro, and TinyLFU-based admission.

## Paper Trail

- R. L. Mattson, J. Gecsei, D. R. Slutz, and I. L. Traiger, "Evaluation
  Techniques for Storage Hierarchies", IBM Systems Journal, 1970.
  DOI: https://doi.org/10.1147/sj.92.0078
- Elizabeth J. O'Neil, Patrick E. O'Neil, and Gerhard Weikum, "The LRU-K Page
  Replacement Algorithm for Database Disk Buffering", SIGMOD 1993.
  DOI: https://doi.org/10.1145/170035.170081
