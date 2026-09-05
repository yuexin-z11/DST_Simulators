# DST Simulators

ECE 6140 circuit simulation projects.

## Part 1: Boolean circuit simulator

Project 1 reads a circuit description, assigns a binary input vector to its declared inputs, evaluates gates in dependency order, and returns a binary output vector. The implementation parses connectivity; it contains no circuit-specific answers.

## Requirements

- Python 3.9 or newer. Only the Python standard library is used; no package installation is needed.
- Circuit description files supplied separately. Circuit files and generated result files are kept locally and ignored by Git.
- A terminal opened in the repository root (`DST_Simulators`). The commands below use `python3`; on Windows, use `py -3` if appropriate.

## File structure

```text
DST_Simulators/
├── README.md             # Setup and usage
├── .gitignore            # Excludes local circuits, results, and Python caches
├── RESUME_SESSION.md     # Session continuation notes
└── p1/
    ├── simulator.py      # Netlist parser, dependency ordering, and simulation CLI
    ├── run_required.py   # Runs the 20 required assignment cases
    ├── test_simulator.py # Logic, validation, and reference-evaluator tests
    ├── README.md         # Project-specific format and usage details
    └── REPORT.md         # Data structures, algorithm, and verification explanation
```

Provide these files locally in `p1/` to run the assignment batch and full tests:

```text
s27.txt
s298f_2.txt
s344f_2.txt
s349f_2.txt
```

These are the assignment's CHAT-format circuit descriptions, supplied with `.txt` extensions. If your copies use `.chat`, give them the corresponding `.txt` filenames for the batch runner and tests. The single-circuit CLI accepts either extension.

## Run one circuit

From the repository root:

```bash
python3 p1/simulator.py p1/s27.txt 1110101
```

Pass additional vectors to simulate the same circuit repeatedly:

```bash
python3 p1/simulator.py p1/s27.txt 1110101 0001010 1010101
```

The program prints tab-separated columns: circuit filename, input vector, and output vector. Each vector must contain only `0` and `1`, with exactly one bit per declared input. Bits follow the file's INPUT and OUTPUT declaration order.

For another circuit file:

```bash
python3 p1/simulator.py path/to/circuit.chat YOUR_BINARY_VECTOR
```

Replace the path and placeholder with your circuit and its binary input vector.

## Run all required cases

After placing all four circuit files in `p1/`:

```bash
python3 p1/run_required.py
```

This runs five vectors per circuit, prints a Markdown table, and writes `p1/results.md` and `p1/results.csv`. Those generated files stay local and are ignored by Git. Existing result files are overwritten when the batch is rerun.

## Run verification

```bash
python3 -m unittest discover -s p1 -v
```

The full suite requires the four local circuit files. It checks gate truth tables, input validation, connectivity, output ordering, and results against an independently parsed recursive evaluator. Reference comparisons include the required vectors, every s27 input vector, and reproducible random vectors for the larger circuits.

Without circuit files, run the self-contained logic and validation checks:

```bash
cd p1
python3 -m unittest -v test_simulator.SimulatorTests.test_truth_tables_and_output_order test_simulator.SimulatorTests.test_dependencies_repeated_fanin_and_fresh_values test_simulator.SimulatorTests.test_invalid_netlists test_simulator.SimulatorTests.test_invalid_vectors
```

## Circuit format and limitations

Gate records contain the gate name, source node(s), and destination node. Supported gates are `INV`, `BUF`, `AND`, `OR`, `NAND`, and `NOR`. INPUT and OUTPUT lists end with `-1`. Gates may appear in any order; the simulator computes a topological order before evaluating them.

This is a combinational Boolean simulator without clock, state, or timing-delay modeling. Invalid syntax, unsupported gates, incorrectly sized vectors, missing drivers, multiple drivers, and dependency cycles are rejected.

See [Project 1 details](p1/README.md) and [report material](p1/REPORT.md).
