# LIRS Eviction Policy

LIRS, or low inter-reference recency set, ranks pages by reuse distance rather
than simple last-access recency. It separates pages with strong locality from
pages with weak or uncertain locality.

## Core Idea

- Classify pages as LIR, meaning low inter-reference recency, or HIR, meaning
  high inter-reference recency.
- Most cache space is reserved for resident LIR pages.
- A small resident HIR set absorbs pages with weak or unproven locality.
- Maintain stack `S` for recency/history and queue `Q` for resident HIR pages.
- Evict from resident HIR pages, not from the protected LIR set.

## Metadata

- Stack `S` containing resident pages and selected nonresident history entries.
- Queue `Q` containing resident HIR pages.
- Page state: LIR, resident HIR, or nonresident HIR.
- Page id to stack/queue node map.

## Expected Behavior

LIRS fixes important LRU weaknesses on scans and loops by using reuse distance
as the locality signal. It tends to be more complex than LRU/2Q and needs careful
stack pruning.

For this benchmark, LIRS should be expected to:

- handle one-time scans without flushing the protected hot set;
- perform well on cyclic loops larger than the cache;
- provide the conceptual basis for CLOCK-Pro.

## Paper Trail

- Song Jiang and Xiaodong Zhang, "LIRS: An Efficient Low Inter-reference
  Recency Set Replacement Policy to Improve Buffer Cache Performance",
  SIGMETRICS 2002. DOI: https://doi.org/10.1145/511334.511340
- Song Jiang, Feng Chen, and Xiaodong Zhang, "CLOCK-Pro: An Effective
  Improvement of the CLOCK Replacement", USENIX Annual Technical Conference
  2005. https://www.usenix.org/legacy/publications/library/proceedings/usenix05/tech/general/full_papers/jiang/jiang.pdf
