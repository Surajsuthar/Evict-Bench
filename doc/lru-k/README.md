# LRU-K Eviction Policy

LRU-K evicts the page whose K-th most recent access is oldest. LRU-1 is ordinary
LRU. LRU-2 is the common database-oriented choice because it requires a second
reference before a page receives strong protection.

## Core Idea

- Keep the last `K` access timestamps for each tracked page.
- Pages with fewer than `K` references are treated as having low confidence.
- On eviction, prefer pages whose K-th most recent timestamp is oldest.
- Use correlated-reference filtering so rapid repeated touches from one logical
  operation do not inflate a page's value.

## Metadata

- Page id to bounded history of access timestamps.
- Priority structure keyed by backward K-distance.
- Retained history for recently evicted pages if the implementation wants to
  preserve inter-arrival information across misses.

## Expected Behavior

LRU-K is designed for database buffering, where a single scan should not be
enough to displace pages with repeated long-term value. It is more expensive than
LRU because it needs access histories and victim ordering by K-distance.

For this benchmark, LRU-K should be expected to:

- outperform LRU on mixed scan plus hot-set traces;
- do well on stable transactional pages with repeated references;
- require careful choices for `K`, retained history, and correlated-reference
  period.

## Paper Trail

- Elizabeth J. O'Neil, Patrick E. O'Neil, and Gerhard Weikum, "The LRU-K Page
  Replacement Algorithm for Database Disk Buffering", SIGMOD 1993.
  DOI: https://doi.org/10.1145/170035.170081
- Theodore Johnson and Dennis Shasha, "2Q: A Low Overhead High Performance
  Buffer Management Replacement Algorithm", VLDB 1994.
  https://www.vldb.org/conf/1994/P439.PDF
