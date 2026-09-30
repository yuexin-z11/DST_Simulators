# Project 1: C++ circuit simulator

## Setup

Use a C++17 compiler (`g++`) and GNU Make. Both are available in the current workspace; no third-party libraries are needed. Commands below start in the repository root. If your terminal is already in `p1/`, use `make` and `./build/...` instead.

```bash
make -C p1
make -C p1 check
./p1/build/simulator p1/s27.txt 1110101 0001010
./p1/build/run_required p1
```

The single-circuit simulator and parsing/scheduling checks are implemented. Input vectors must contain only binary digits and match the declared input count. The parser assumes valid supplied circuit files. The batch runner takes the circuit directory as its required argument, runs all 20 vectors, and prints four labeled tables. It writes `results.md` and `results.csv` in that directory, overwriting previous results. Follow [TODO.md](TODO.md) for remaining work.

## Structure

| File | Purpose |
| --- | --- |
| `include/circuit.hpp` | Gate/Circuit data structures and function declarations. |
| `src/circuit.cpp` | Your parser, gate logic, and queue-based simulation. |
| `src/main.cpp` | Command-line wrapper: circuit path followed by input vectors. |
| `src/run_required.cpp` | Runs the 20 required vectors and exports Markdown/CSV results. |
| `tests/test_circuit.cpp` | Parsing and simulation checkpoints to expand. |
| `tests/small.net` | Tiny circuit with gates intentionally out of dependency order. |
| `REPORT.md` | Data structures, algorithm pseudocode, and all 20 simulation results. |
| `report_tables.xlsx` | Excel workbook with the data structures and four simulation result tables. |
| `figures/` | Circuit-specific screenshots referenced by the report. |

Four circuit descriptions are present locally as `s27.txt`, `s298f_2.txt`, `s344f_2.txt`, and `s349f_2.txt`. Confirm they correspond to the assignment's .chat files. The handout does not define the file syntax; implement against the supplied descriptions. Circuit inputs and generated outputs are ignored by Git.

Generated `results.md` and `results.csv` remain local and are ignored by Git. Binary vectors are written as strings to preserve leading zeros; import CSV vector columns as text when using a spreadsheet.
