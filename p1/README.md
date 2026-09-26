# Project 1: C++ circuit simulator starter

## Setup

Use a C++17 compiler (`g++`) and GNU Make. Both are available in the current workspace; no third-party libraries are needed. Commands below start in the repository root. If your terminal is already in `p1/`, use `make` and `./build/...` instead.

```bash
make -C p1
make -C p1 check
./p1/build/simulator p1/s27.txt 1110101 0001010
./p1/build/run_required p1
```

The starter builds, but the check and simulator stop at unfinished methods. The batch runner is also a placeholder. Follow [TODO.md](TODO.md) one milestone at a time.

## Structure

| File | Purpose |
| --- | --- |
| `include/circuit.hpp` | Gate/Circuit data structures and function declarations. |
| `src/circuit.cpp` | Your parser, gate logic, and queue-based simulation. |
| `src/main.cpp` | Command-line wrapper: circuit path followed by input vectors. |
| `src/run_required.cpp` | The 20 required vectors and unfinished batch runner. |
| `tests/test_circuit.cpp` | Parsing and simulation checkpoints to expand. |
| `tests/small.net` | Tiny circuit with gates intentionally out of dependency order. |
| `REPORT.md` | Report template: two written pages plus simulation data. |

Four circuit descriptions are present locally as `s27.txt`, `s298f_2.txt`, `s344f_2.txt`, and `s349f_2.txt`. Confirm they correspond to the assignment's .chat files. The handout does not define the file syntax; implement against the supplied descriptions. Circuit inputs and generated outputs are ignored by Git.

The local `results.md` and `results.csv` are historical outputs from the previous Python implementation. Regenerate results with your completed C++ simulator before using them in the report.
