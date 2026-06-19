# CLOCK Eviction Policy

CLOCK approximates LRU with a circular list and a reference bit. It is cheaper
than moving a page on every hit and is widely used as an operating-system style
replacement primitive.

## Core Idea

- Store pages in circular order with a clock hand.
- Each page has a reference bit.
- On hit, set the reference bit.
- On eviction, advance the hand until it finds a page with reference bit `0`.
- Pages with reference bit `1` get a second chance: clear the bit and continue.

## Metadata

- Circular array or list of resident frames.
- One reference bit per resident frame.
- Page id to frame index map.
- Clock hand index.

## Expected Behavior

CLOCK usually tracks LRU behavior with lower maintenance cost. It can still
suffer from the same scan and cyclic-loop weaknesses because the reference bit
contains only a small amount of history.

For this benchmark, CLOCK should be expected to:

- approximate LRU on common hot-set traces;
- reduce per-access policy update cost versus exact LRU;
- serve as the baseline for PostgreSQL-style clock sweep, CLOCK-Pro, and CAR.

## Paper Trail

- Fernando J. Corbato, "A Paging Experiment with the Multics System", in In
  Honor of P. M. Morse, MIT Press, 1969.
- Song Jiang, Feng Chen, and Xiaodong Zhang, "CLOCK-Pro: An Effective
  Improvement of the CLOCK Replacement", USENIX Annual Technical Conference
  2005. https://www.usenix.org/legacy/publications/library/proceedings/usenix05/tech/general/full_papers/jiang/jiang.pdf
