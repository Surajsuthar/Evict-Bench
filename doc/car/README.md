# CAR Eviction Policy

CAR, or clock with adaptive replacement, combines ARC's adaptive recency versus
frequency balance with CLOCK-style lists and reference bits.

## Core Idea

CAR mirrors ARC's four-list structure with CLOCK-like resident lists:

- `T1`: resident recent pages.
- `T2`: resident frequent pages.
- `B1`: ghost history for pages evicted from `T1`.
- `B2`: ghost history for pages evicted from `T2`.

Unlike ARC, resident lists use reference bits and clock hands rather than exact
LRU movement on every hit. Ghost hits adapt the target size for `T1`.

## Metadata

- Two resident CLOCK lists.
- Two ghost lists storing page ids.
- Reference bit per resident page.
- Adaptive target `p`.
- Page id to list/state map.

## Expected Behavior

CAR targets ARC-like hit rates with lower hit-path overhead. It should adapt to
recency-heavy and frequency-heavy phases while avoiding exact LRU list movement
on every access.

For this benchmark, CAR should be expected to:

- perform comparably to ARC on many traces;
- cost less per hit than ARC in implementations where list movement is expensive;
- outperform plain CLOCK on scan-heavy and mixed workloads.

## Paper Trail

- Sorav Bansal and Dharmendra S. Modha, "CAR: Clock with Adaptive Replacement",
  FAST 2004. https://www.usenix.org/legacy/events/fast04/tech/full_papers/bansal/bansal.pdf
- Nimrod Megiddo and Dharmendra S. Modha, "ARC: A Self-Tuning, Low Overhead
  Replacement Cache", FAST 2003.
  https://www.usenix.org/legacy/events/fast03/tech/full_papers/megiddo/megiddo.pdf
