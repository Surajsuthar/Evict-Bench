#pragma once

#include "evict-benchmark/comman/type.h"
#include "evict-benchmark/workload/workload-type.h"
#include <cstddef>
#include <vector>

namespace evictbench {

// Generates page-reference traces for exercising eviction algorithms.
//
// Every generator should return one WorkloadTypeInfo per simulated access:
//   * page_id identifies the page being accessed.
//   * timestamps must be monotonic so consumers can reconstruct access order.
//
// A useful implementation also needs a request count, page-id range and random
// seed. These are not currently present in the API; add them as constructor or
// method parameters instead of hiding fixed values in the implementation.
class WorkLoad {
public:
  // Draw page ranks with probability P(rank = k) proportional to 1 / k^s,
  // where s is the skew parameter. Build the normalized cumulative distribution
  // for ranks [1, page_count], sample it with a seeded RNG, and convert each
  // rank to a page_id. Larger s values produce a smaller, hotter working set.
  std::vector<WorkloadTypeInfo> ZipfWorkload(std::size_t length);

  // Use a seeded uniform integer distribution over the complete page-id range.
  // Each page must have equal probability on every independent access; this is
  // the baseline workload with no locality or intentionally hot pages.
  std::vector<WorkloadTypeInfo> UniformWorkload(std::size_t length);

  // Visit page ids in increasing order. After the last page, either stop or
  // wrap to the first page until request_count entries have been emitted.
  // Wrapping models repeated scans and should be documented by the
  // implementation.
  std::vector<WorkloadTypeInfo> SequentialWorkload(std::size_t length);

  // Approximate an OLTP trace by combining locality and occasional cold access:
  // choose a hot working set, send most requests to it (often with Zipf skew),
  // and send the remainder uniformly to cold pages. Optionally group accesses
  // into short transactions to model repeated index/data-page reuse.
  std::vector<WorkloadTypeInfo> OLTPWorkload(std::size_t length);

  // Repeatedly traverse a bounded working set in a fixed cycle, for example
  // page_id = cycle_start + (access_index % cycle_size). A cycle slightly
  // larger than cache capacity is useful for exposing scan-resistance problems.
  std::vector<WorkloadTypeInfo> CyclicWorkload(std::size_t length,
                                               std::size_t cycle_size);

  // Divide the page universe into hot and cold sets. Route most accesses (for
  // example, 80%) uniformly or with Zipf skew to the first hot_size pages and
  // route the remainder uniformly to the cold set. The implementation must
  // define the total page count and validate that 0 < hot_size < page_count.
  std::vector<WorkloadTypeInfo> HotColdLoad(std::size_t length,
                                            std::size_t hot_size);

  // Model short-lived popularity by selecting a page or small working set and
  // issuing burst_size consecutive accesses to it before selecting the next
  // target. Repeat until length entries are emitted, truncating the final burst
  // when necessary. A seeded RNG and a defined page range make runs repeatable.
  std::vector<WorkloadTypeInfo> BurstyWorkload(std::size_t length,
                                               std::size_t phase_length,
                                               PageId pages_per_phase);
};
} // namespace evictbench
