# ARC Eviction Policy

ARC, or adaptive replacement cache, balances recency and frequency without a
fixed tuning parameter. It keeps both resident lists and ghost lists so misses
can teach the policy what it recently evicted.

## Core Idea

ARC maintains four LRU lists:

- `T1`: resident pages seen recently once.
- `T2`: resident pages seen frequently or at least twice.
- `B1`: ghost entries evicted from `T1`.
- `B2`: ghost entries evicted from `T2`.

A target parameter `p` controls the preferred size of `T1`. Ghost hits adapt
`p`: a hit in `B1` means recent pages need more space, while a hit in `B2` means
frequent pages need more space.

## Metadata

- Two resident LRU lists.
- Two ghost LRU lists storing only page ids.
- Page id to list/state map.
- Adaptive target `p`.

## Expected Behavior

ARC is designed to resist scans and adapt between recency-oriented and
frequency-oriented workloads. It can perform well without workload-specific
tuning, but it has more metadata and implementation complexity than LRU or 2Q.

For this benchmark, ARC should be expected to:

- outperform LRU on mixed scan and hot-set traces;
- adapt to workload shifts faster than fixed-size 2Q variants;
- provide a strong non-clairvoyant baseline against OPT.

## Paper Trail

- Nimrod Megiddo and Dharmendra S. Modha, "ARC: A Self-Tuning, Low Overhead
  Replacement Cache", FAST 2003.
  https://www.usenix.org/legacy/events/fast03/tech/full_papers/megiddo/megiddo.pdf,
  https://www.usenix.org/system/files/login/articles/1180-Megiddo.pdf
- Nimrod Megiddo and Dharmendra S. Modha, "Outperforming LRU with an Adaptive
  Replacement Cache Algorithm", IEEE Computer, 2004.
