# DBMIN Query-Aware Replacement

DBMIN is a database buffer management strategy that uses query execution context
to choose replacement behavior. Instead of one global rule for all pages, it
groups pages by access pattern and allocates buffer space according to each
operator's needs.

## Core Idea

- The query processor tells the buffer manager about the access pattern for each
  file or operator.
- Pages are grouped into locality sets.
- Each locality set receives a buffer allocation based on its expected reuse.
- Replacement within a locality set can use a policy suited to that pattern,
  such as MRU for looping sequential scans or LRU for random reuse.

## Metadata

- Query/operator id to locality set.
- Locality set descriptors with access-pattern type and buffer target.
- Per-set replacement structure.
- Page id to owning locality set and frame state.

## Expected Behavior

DBMIN is not a simple blind cache policy. It can outperform generic replacement
when the optimizer or execution engine provides accurate hints. Its weakness is
integration complexity and sensitivity to incorrect or stale query knowledge.

For this benchmark, DBMIN should be expected to:

- do well on join-like, scan, and operator-aware synthetic traces;
- outperform global LRU when query phases are known;
- require workload traces to include enough semantic information to be fair.

## Paper Trail

- Hong-Tai Chou and David J. DeWitt, "An Evaluation of Buffer Management
  Strategies for Relational Database Systems", VLDB 1985.
  https://www.vldb.org/conf/1985/P127.PDF
- Wolfgang Effelsberg and Theo Haerder, "Principles of Database Buffer
  Management", ACM TODS, 1984. DOI: https://doi.org/10.1145/357775.357784
