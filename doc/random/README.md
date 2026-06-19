# Random Eviction Policy

Random replacement evicts an arbitrary resident page, usually selected uniformly
from the current cache contents. It deliberately avoids recency or frequency
tracking.

## Core Idea

- On hit, update no policy metadata beyond membership.
- On miss with free capacity, insert the page.
- On miss when full, choose one resident page randomly and replace it.

## Metadata

- Resident page array or vector for O(1) random victim selection.
- Page id to array index map for O(1) membership and removal.
- Pseudorandom generator state.

## Expected Behavior

Random is a useful low-overhead control policy. It avoids the deterministic
pathologies of FIFO and LRU on some cyclic traces, but it does not exploit
locality well when recent or frequent access is predictive.

For this benchmark, Random should be expected to:

- provide a noise-tolerant baseline across workloads;
- sometimes beat LRU on loops slightly larger than cache capacity;
- lose to recency, frequency, or adaptive policies on skewed hot/cold traces.

## Paper Trail

- Laszlo A. Belady, "A Study of Replacement Algorithms for a Virtual-Storage
  Computer", IBM Systems Journal, 1966. DOI: https://doi.org/10.1147/sj.52.0078
- Michael W. Rhodehamel, "The Bus Interface and Paging Units of the i860
  Microprocessor", IEEE, 1989.
