# Boolean circuit simulator

A C++17 simulator for combinational circuits described as node declarations and logic gates. It reads a circuit once, evaluates one or more binary input vectors, and prints the output bits in declared order. A separate batch runner evaluates 20 preset vectors across four benchmark circuits and exports Markdown and CSV results.

## Build and try the included example

Prerequisites: `g++` with C++17 support and GNU Make. No third-party libraries are needed. Run these commands from the repository root:

```bash
make -C p1
make -C p1 check
./p1/build/simulator p1/tests/small.net 11 10
```

The final command prints output vectors `0` for `11` and `1` for `10`. If you are already in `p1/`, use `make`, `make check`, and `./build/simulator tests/small.net 11 10`.

The CLI accepts a circuit path followed by one or more input vectors:

```text
simulator CIRCUIT_FILE INPUT_VECTOR [INPUT_VECTOR ...]
```

## Circuit file format

Each line contains an uppercase keyword followed by node IDs. `INPUT` and `OUTPUT` declarations end with `-1`. Unary gates use `OP source destination`; binary gates use `OP source1 source2 destination`. The supported operations are `INV`, `BUF`, `AND`, `OR`, `NAND`, and `NOR`.

The included [small circuit](tests/small.net) shows that gates can appear before the gates that supply their inputs:

```text
INV 3 4
AND 1 2 3
INPUT 1 2 -1
OUTPUT 4 -1
```

For this file, the first input bit belongs to node `1`, the second to node `2`, and the output bit comes from node `4`. Node IDs need not be consecutive. Gate order does not determine evaluation order; the simulator schedules a gate when all its source values are available.

## Assumptions and behavior

- Input vectors must contain only `0` and `1` and have one bit per declared input node. Each vector starts a fresh simulation state, so earlier runs cannot affect later ones.
- Inputs and outputs retain their declaration order, including leading zeros in the result string.
- Circuit files are expected to be well formed, with one driver per gate destination and every gate source resolvable from an input or another gate. The parser does not fully validate malformed files.
- A dependency cycle or missing gate source stops simulation with an error. The simulator models combinational logic only; it does not model clocks, stored state, or propagation delay.

## Batch benchmarks

The batch runner expects `s27.txt`, `s298f_2.txt`, `s344f_2.txt`, and `s349f_2.txt` in the directory passed to it. These input descriptions are kept locally and are not included in this repository. Add them before running:

```bash
./p1/build/run_benchmarks p1
```

The runner prints four result tables and writes `results.md` and `results.csv` beside the circuit files. Repeated runs overwrite those generated files, which Git ignores. The checked-in [Excel workbook](report_tables.xlsx) is a static snapshot of the data-structure summary and simulation results; running the simulator does not update it. Binary vectors are stored as text in the workbook to preserve leading zeros.

## Project files

| File | Purpose |
| --- | --- |
| `include/circuit.hpp` | Gate and circuit data structures and public interfaces. |
| `src/circuit.cpp` | Parser, Boolean gate evaluation, and dependency-based scheduling. |
| `src/main.cpp` | CLI for simulating one circuit with one or more vectors. |
| `src/run_benchmarks.cpp` | Batch runner and Markdown/CSV exports. |
| `tests/small.net` | Tracked example with gates out of dependency order. |
| `tests/test_circuit.cpp` | Parsing, truth-table, input-validation, and scheduling checks. |
| `report_tables.xlsx` | Excel summary and four benchmark result tables. |

See [project status](TODO.md) for current limitations and next steps.
