# CLOCK-Pro Eviction Policy

CLOCK-Pro adapts LIRS ideas to a CLOCK-like implementation. It keeps hot, cold,
and test pages on clock lists so it can use reuse-distance-style history with
lower operating-system-style overhead.

## Core Idea

- Classify pages as hot or cold.
- Keep nonresident test pages to remember recently evicted cold pages.
- Use clock hands to scan hot pages, cold pages, and test pages.
- A hit on a test page indicates that cold pages deserve more space.
- A cold page that is reused can be promoted to hot.

## Metadata

- Circular list entries for resident hot pages, resident cold pages, and
  nonresident test pages.
- Reference bits or equivalent access markers.
- Page id to state/list entry map.
- Target size for cold resident pages.

## Expected Behavior

CLOCK-Pro aims to keep CLOCK's low-overhead style while adding LIRS-like scan and
loop resistance. It is a good fit for benchmarking because it sits between
simple CLOCK and more metadata-heavy LIRS.

For this benchmark, CLOCK-Pro should be expected to:

- beat CLOCK and LRU on scans and loops with weak locality;
- approach LIRS behavior with cheaper replacement scans;
- require careful validation of hot/cold/test transitions.

## Paper Trail

- Song Jiang, Feng Chen, and Xiaodong Zhang, "CLOCK-Pro: An Effective
  Improvement of the CLOCK Replacement", USENIX Annual Technical Conference
  2005. https://www.usenix.org/legacy/publications/library/proceedings/usenix05/tech/general/full_papers/jiang/jiang.pdf
- Song Jiang and Xiaodong Zhang, "LIRS: An Efficient Low Inter-reference
  Recency Set Replacement Policy to Improve Buffer Cache Performance",
  SIGMETRICS 2002. DOI: https://doi.org/10.1145/511334.511340
