# MRU Eviction Policy

MRU, or most recently used, evicts the page that was accessed most recently. It
is intentionally opposite to LRU and is mainly useful for workloads where the
latest page is least likely to be reused.

## Core Idea

- Keep resident pages ordered by recency.
- On hit, mark the page as most recent.
- On miss, insert the page as most recent.
- On eviction, remove the most-recent page.

## Metadata

- Recency list or stack.
- Page id to list node map.

## Expected Behavior

MRU is rarely a good default cache policy, but it is important in database
benchmarking because repeated sequential scans can make LRU evict the exact
pages that will be needed next. Under cyclic scan patterns over a relation
larger than the cache, MRU can retain older pages that are closer to reuse.

For this benchmark, MRU should be expected to:

- beat LRU on looping sequential scans larger than the cache;
- perform poorly on conventional temporal-locality traces;
- clarify whether a workload is scan-dominated rather than hot-set dominated.

## Paper Trail

- Hong-Tai Chou and David J. DeWitt, "An Evaluation of Buffer Management
  Strategies for Relational Database Systems", VLDB 1985.
  https://www.vldb.org/conf/1985/P127.PDF
- Shaul Dar, Michael J. Franklin, Bjorn Thor Jonsson, Divesh Srivastava, and
  Michael Tan, "Semantic Data Caching and Replacement", VLDB 1996.
