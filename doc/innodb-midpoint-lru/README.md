# InnoDB Midpoint LRU

InnoDB manages its buffer pool with a modified LRU list that inserts newly read
pages near the midpoint instead of at the most-recent end. The list is split into
young and old regions.

## Core Idea

- Keep one LRU list with a young/new sublist at the head and an old sublist at
  the tail.
- Insert newly read pages at the midpoint, which is the head of the old sublist.
- Promote an old page to the young head after qualifying access.
- Evict from the tail of the old sublist.
- Use configuration such as old-sublist percentage and old-block time to reduce
  scan pollution.

## Metadata

- LRU list with a midpoint boundary.
- Page id to list node map.
- Per-page state for young versus old.
- Optional timestamps to enforce promotion delay for scan resistance.

## Expected Behavior

Midpoint insertion prevents a one-time scan from immediately occupying the most
protected part of the cache. It is a production database variant of LRU tuned for
mixed OLTP and scan-heavy access.

For this benchmark, InnoDB midpoint LRU should be expected to:

- improve over plain LRU on sequential scans mixed with hot pages;
- behave similarly to LRU once pages are promoted to the young sublist;
- depend on the old-region size and promotion-delay parameters.

## Paper And Source Trail

- MySQL 8.4 Reference Manual, "Buffer Pool LRU Algorithm":
  https://dev.mysql.com/doc/refman/8.4/en/innodb-buffer-pool.html
- Hong-Tai Chou and David J. DeWitt, "An Evaluation of Buffer Management
  Strategies for Relational Database Systems", VLDB 1985.
  https://www.vldb.org/conf/1985/P127.PDF
