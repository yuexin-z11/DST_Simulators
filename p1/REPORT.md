# ECE 6140 Project 1 — Circuit Simulation

## Data structures (main report, page 1)

The simulator represents the circuit as a directed graph: numbered nodes carry binary signals, and gates calculate destination nodes from source nodes. Each `Gate` record stores its logic type (`kind`), a tuple of source node numbers (`fanin`), and its destination node number (`output`). The `Circuit` object holds ordered tuples of primary inputs, primary outputs, gates, and a precomputed gate evaluation order.

Input and output tuples preserve the order in the file declarations. The first input-vector bit belongs to the first declared input, and the first output-vector bit comes from the first declared output. Node numbers are identifiers, not vector positions. For example, s27 declares inputs `1 2 3 4 6 8 10` and outputs `7 9 11 5`.

During preprocessing, a `drivers` dictionary maps destination nodes to their producing gates. A `consumers` dictionary lists gates that depend on each gate-produced node. A `waiting` dictionary counts each gate's distinct unresolved dependencies, and a queue holds gates ready for scheduling. During simulation, a fresh `values` dictionary maps each node number to its computed bit, 0 or 1. Recreating this dictionary prevents values from leaking between input vectors.

The supplied descriptions have `.txt` extensions. Each gate line gives its type, source node(s), and destination node, in that order. `INV` and `BUF` have one source; `AND`, `OR`, `NAND`, and `NOR` have two. `INPUT` and `OUTPUT` lines end with the sentinel `-1`, which is not a node. Blank lines and ordinary whitespace are accepted. The parser does not depend on the filename extension. These files contain only combinational gates; every declared input is supplied by the vector.

## Simulation algorithm (main report, page 2)

The file order is not a valid evaluation order because gates may reference nodes produced later in the file. The simulator therefore computes a topological order once and reuses it for every vector.

```text
LOAD CIRCUIT(file):
    Read each nonblank line.
    For INPUT/OUTPUT, save nodes in listed order, excluding final -1.
    For a gate, save its type, source nodes, and destination node.
    Validate syntax, gate arity, declarations, and unique drivers.
    Reject references to nodes with no source.
    For each gate:
        Count distinct sources driven by other gates.
        Register this gate as a consumer of those sources.
    Enqueue every gate with count zero (primary inputs are ready).
    While the queue is nonempty:
        Remove a gate and append it to the evaluation order.
        Decrement the count of each consumer of its destination.
        Enqueue consumers whose counts become zero.
    If any gate remains unscheduled, reject the dependency cycle.

SIMULATE(circuit, vector):
    Require binary digits and exactly one bit per declared input.
    Create a fresh node-value dictionary.
    Assign bits to input nodes in declaration order.
    For each gate in the evaluation order:
        Read the values of its source nodes.
        Apply its Boolean operation and save its destination value.
    Concatenate output-node values in OUTPUT declaration order.
    Return the resulting binary string.
```

`BUF` copies its input and `INV` complements it. `AND` produces 1 when both inputs are 1; `OR` produces 1 when either input is 1. `NAND` and `NOR` complement those respective results. The simulation represents settled Boolean behavior, without timing delays. With N nodes, G gates, and E gate-input connections, preprocessing and each simulation take O(N + G + E) time at most; storage is O(N + G + E).

## Simulation-data tables

The complete 20-row table is in [results.md](results.md); [results.csv](results.csv) provides the same data for import. Preserve vector columns as text in spreadsheets to retain leading zeros. Circuit labels use the assignment's `.chat` names; the actual supplied files use `.txt`.

## Verification notes (supporting material)

The tests use an independent parser and a recursive, memoized evaluator with explicit truth tables. Comparisons cover all 20 required cases, all 128 s27 vectors, and 1,000 reproducible random vectors plus all-zero and all-one vectors for each larger circuit (3,154 comparisons total). Gate truth tables, output ordering, shuffled gate order, repeated fan-in, fresh values between runs, malformed netlists, invalid vectors, undriven nodes, duplicate drivers, and cycles are also checked. This is an independent implementation cross-check; no instructor-provided output oracle was available.
