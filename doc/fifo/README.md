# FIFO Eviction Policy

FIFO, or first-in first-out, evicts the page that has been resident in the cache
for the longest time. It ignores recency after admission: a page that is hit many
times is still evicted when it reaches the head of the queue.

## Core Idea

- On miss with free capacity, append the new page to the tail of a resident
  queue.
- On hit, leave the page in its current queue position.
- On eviction, remove the page at the queue head.

## Metadata

- Resident membership table: page id to queue node or presence bit.
- FIFO queue containing resident pages in admission order.

The policy can be implemented with O(1) hit, insert, remove, and evict if the
membership table stores queue iterators.

## Expected Behavior

FIFO is useful as a baseline because it has very low metadata overhead and no
tuning parameters. It can perform poorly when old pages are still hot, because
hits do not protect pages from eviction. It is also known for Belady's anomaly:
larger cache capacity can produce more misses on some traces.

For this benchmark, FIFO should be expected to:

- handle pure scans predictably with one miss per new page;
- underperform LRU-like policies on stable hot sets;
- expose the impact of metadata simplicity versus hit-rate quality.

## Paper Trail

- Laszlo A. Belady, "A Study of Replacement Algorithms for a Virtual-Storage
  Computer", IBM Systems Journal, 1966. DOI: https://doi.org/10.1147/sj.52.0078
- General page replacement background:
  https://en.wikipedia.org/wiki/Page_replacement_algorithm
