# evict-benchmark

C++ benchmark suite for database buffer-pool eviction policies: FIFO, Random, LRU, MRU, CLOCK, LFU, LFU-Aging, LRU-K, 2Q, PostgreSQL-style Clock Sweep, InnoDB midpoint LRU, ARC, LIRS, CLOCK-Pro, CAR, TinyLFU, and DBMIN-style query-aware replacement.

Policy research notes and implementation guidance live under
[`doc/`](doc/README.md), with one README per eviction algorithm.

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
./dbcache_bench
ctest --output-on-failure
```

## Current status

This repo is a scaffold. The root benchmark target builds the current source
tree, but the eviction policies are not fully implemented yet. The `doc/`
directory defines the intended behavior, metadata, benchmark expectations, and
paper references for each planned policy.

## Project goal

Benchmark classical, database-specific, scan-resistant, frequency-based, and adaptive eviction policies across synthetic DB-like traces.

## Metrics

- Hit rate
- Miss rate
- Evictions
- Dirty evictions
- Runtime
- Metadata overhead
- Scan pollution score
- Adaptation speed

## Workloads

- Sequential scan
- Looping scan
- Hot/cold
- Zipfian
- Mixed OLTP + analytics
- Bursty
- Join-like pattern
