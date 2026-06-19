# PostgreSQL-Style Clock Sweep

PostgreSQL uses a clock-sweep style buffer replacement algorithm with a small
usage counter per buffer. It is closer to generalized CLOCK than to a single-bit
CLOCK policy.

## Core Idea

- Maintain a global sweep hand over buffer descriptors.
- Each buffer has a `usage_count`.
- A hit increments `usage_count` up to an implementation-defined cap.
- The sweep hand looks for an unpinned buffer with `usage_count == 0`.
- If an unpinned buffer has positive `usage_count`, decrement it and continue.
- PostgreSQL also has buffer access strategy rings for bulk reads, vacuum, and
  similar access patterns so scans do not fully pollute the shared buffer pool.

## Metadata

- Frame array with pin state and dirty state.
- Usage counter per frame.
- Clock hand index.
- Optional per-operation ring buffers for scan-like access strategies.

## Expected Behavior

This policy is practical for a concurrent DBMS because it avoids maintaining an
exact LRU list under contention. The usage counter gives frequently hit pages
more than one second chance while still allowing aging.

For this benchmark, PostgreSQL-style clock sweep should be expected to:

- behave like CLOCK with frequency-biased second chances;
- resist some scans better when access-strategy rings are modeled;
- show lower metadata churn than exact LRU.

## Paper And Source Trail

- PostgreSQL source, `freelist.c`, especially `ClockSweepTick` and
  `StrategyGetBuffer`:
  https://github.com/postgres/postgres/blob/master/src/backend/storage/buffer/freelist.c
- PostgreSQL runtime resource documentation:
  https://www.postgresql.org/docs/current/runtime-config-resource.html
- Richard W. Carr and John L. Hennessy, "WSCLOCK - A Simple and Effective
  Algorithm for Virtual Memory Management", SOSP 1981.
  DOI: https://doi.org/10.1145/800216.806596
