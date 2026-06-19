# 2Q Eviction Policy

2Q is a low-overhead, scan-resistant replacement policy that approximates the
benefits of LRU-2 with queues rather than a priority queue. It distinguishes
first-time pages from pages that have been referenced again.

## Core Idea

The full 2Q policy uses three queues:

- `A1in`: resident FIFO queue for pages seen once recently.
- `Am`: resident LRU queue for pages seen at least twice.
- `A1out`: nonresident ghost FIFO queue remembering pages evicted from `A1in`.

Access behavior:

- Hit in `Am`: move to the MRU end of `Am`.
- Hit in `A1in`: usually keep in `A1in` until it leaves, depending on variant.
- Miss with page in `A1out`: admit to `Am`; this is evidence of reuse.
- Cold miss: admit to `A1in`.

## Metadata

- Resident membership for `A1in` and `Am`.
- Ghost membership for `A1out`.
- Queue sizes, usually with `A1in` and `A1out` bounded as fractions of capacity.

## Expected Behavior

2Q prevents one-time scan pages from immediately entering the protected main LRU
queue. It has constant-time operations and usually needs less tuning than LRU-K,
though queue sizing still matters.

For this benchmark, 2Q should be expected to:

- protect hot pages during large scans;
- perform close to LRU on simple temporal-locality traces;
- improve over LRU on database traces where second references are meaningful.

## Paper Trail

- Theodore Johnson and Dennis Shasha, "2Q: A Low Overhead High Performance
  Buffer Management Replacement Algorithm", VLDB 1994.
  https://www.vldb.org/conf/1994/P439.PDF
- Elizabeth J. O'Neil, Patrick E. O'Neil, and Gerhard Weikum, "The LRU-K Page
  Replacement Algorithm for Database Disk Buffering", SIGMOD 1993.
  DOI: https://doi.org/10.1145/170035.170081
