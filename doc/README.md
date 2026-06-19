# Eviction Policy Notes

This directory documents the eviction policies named in the root README. Each
policy has its own `doc/<policy>/README.md` page with:

- the eviction rule and metadata required;
- expected behavior on database-style traces;
- implementation notes for this benchmark;
- primary paper or source references.

The current codebase is still a scaffold. These notes describe the intended
policy semantics so implementations and benchmark reports can be checked against
the same definitions.

## Policies

- [FIFO](fifo/README.md)
- [Random](random/README.md)
- [LRU](lru/README.md)
- [MRU](mru/README.md)
- [CLOCK](clock/README.md)
- [LFU](lfu/README.md)
- [LFU-Aging](lfu-aging/README.md)
- [LRU-K](lru-k/README.md)
- [2Q](2q/README.md)
- [PostgreSQL-style Clock Sweep](postgres-clock-sweep/README.md)
- [InnoDB Midpoint LRU](innodb-midpoint-lru/README.md)
- [ARC](arc/README.md)
- [LIRS](lirs/README.md)
- [CLOCK-Pro](clock-pro/README.md)
- [CAR](car/README.md)
- [TinyLFU](tinylfu/README.md)
- [DBMIN](dbmin/README.md)
- [OPT](opt/README.md)
