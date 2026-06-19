# OPT Eviction Policy

OPT, also called MIN or Belady's optimal replacement policy, evicts the resident
page whose next access is farthest in the future. If a resident page is never
used again, it is the best victim.

## Core Idea

- The policy is clairvoyant: it requires the full future reference trace.
- On each miss when the cache is full, inspect the next-use position of every
  resident page.
- Evict the page with the farthest next use, or no future use.

## Metadata

- Full workload trace or per-page queue of future access positions.
- Resident membership set.
- For efficient simulation, page id to queue of future indices.

## Expected Behavior

OPT is not implementable in an online DBMS because real systems do not know the
future. It is still essential in a benchmark suite because it gives an upper
bound on achievable hit rate for a fixed trace and cache size.

For this benchmark, OPT should be expected to:

- produce the best possible hit rate for a replayed trace;
- quantify the gap between practical policies and the theoretical optimum;
- validate trace difficulty across cache capacities.

## Paper Trail

- Laszlo A. Belady, "A Study of Replacement Algorithms for a Virtual-Storage
  Computer", IBM Systems Journal, 1966. DOI: https://doi.org/10.1147/sj.52.0078
- Alfred V. Aho, Peter J. Denning, and Jeffrey D. Ullman, "Principles of
  Optimal Page Replacement", Journal of the ACM, 1971.
  DOI: https://doi.org/10.1145/321623.321632
