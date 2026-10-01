# Boolean circuit simulator

## Setup

Use a C++17 compiler (`g++`) and GNU Make. Both are available in the current workspace; no third-party libraries are needed. Commands below start in the repository root. If your terminal is already in `p1/`, use `make` and `./build/...` instead.

```bash
make -C p1
make -C p1 check
./p1/build/simulator p1/s27.txt 1110101 0001010
./p1/build/run_benchmarks p1
```

The single-circuit simulator accepts binary input vectors that match the declared input count. The batch runner takes a circuit directory, runs 20 benchmark vectors across four circuits, and writes `results.md` and `results.csv` beside the circuit files. Repeated runs overwrite those generated files. See [project status](TODO.md) for current limitations and next steps.

## Structure

| File | Purpose |
| --- | --- |
| `include/circuit.hpp` | Gate/Circuit data structures and function declarations. |
| `src/circuit.cpp` | Circuit parser, gate logic, and queue-based simulation. |
| `src/main.cpp` | Command-line wrapper: circuit path followed by input vectors. |
| `src/run_benchmarks.cpp` | Runs the 20 benchmark vectors and exports Markdown/CSV results. |
| `tests/test_circuit.cpp` | Parsing, simulation, and scheduling checks. |
| `tests/small.net` | Tiny circuit with gates intentionally out of dependency order. |
| `REPORT.md` | Data structures, algorithm pseudocode, and all 20 simulation results. |
| `report_tables.xlsx` | Excel workbook with the data structures and four simulation result tables. |
| `figures/` | Circuit-specific screenshots referenced by the report. |

The batch runner expects `s27.txt`, `s298f_2.txt`, `s344f_2.txt`, and `s349f_2.txt` in the directory passed to it. These circuit descriptions are kept locally and ignored by Git, so add them before running the batch command in a fresh checkout. The parser expects valid circuit syntax.

Generated `results.md` and `results.csv` remain local and are ignored by Git. Binary vectors are written as strings to preserve leading zeros; import CSV vector columns as text when using a spreadsheet.
