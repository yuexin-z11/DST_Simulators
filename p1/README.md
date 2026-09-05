# ECE 6140 Project 1

## Requirements and setup

Use Python 3.9 or newer; no third-party packages are required. Run the commands below from the repository root. Circuit descriptions are not included in Git: supply `s27.txt`, `s298f_2.txt`, `s344f_2.txt`, and `s349f_2.txt` locally in this folder for the batch runner and full tests. These files contain CHAT-format descriptions. The CLI also accepts `.chat` filenames directly.

## Run the simulator

```bash
python3 p1/simulator.py p1/s27.txt 1110101 0001010
```

Arguments are the circuit path followed by one or more binary input vectors. Output consists of tab-separated circuit, input-vector, and output-vector columns. The vector length must equal the number of declared inputs.

Run all 20 assignment cases:

```bash
python3 p1/run_required.py
```

This prints a table and generates `results.md` and `results.csv` beside the script. Existing tables are overwritten. Circuit files and generated results remain local and are ignored by Git.

Run the complete verification suite after supplying all four circuits:

```bash
python3 -m unittest discover -s p1 -v
```

## File guide

| File | Purpose |
|---|---|
| `simulator.py` | Parser, gate records, circuit representation, topological ordering, Boolean evaluation, and CLI |
| `run_required.py` | Required input vectors and table generation; contains no expected outputs |
| `test_simulator.py` | Truth-table tests, error handling, and independent recursive reference comparisons |
| `REPORT.md` | Concise data-structure explanation, algorithm/pseudocode, and verification notes |
| `*.txt` / `*.chat` | User-supplied circuit descriptions; local only |
| `results.md` / `results.csv` | Generated input/output tables; local only |
| `../RESUME_SESSION.md` | Session continuation notes outside the project folder |

## Verified file syntax

```text
INV source destination
BUF source destination
AND source1 source2 destination
OR source1 source2 destination
NAND source1 source2 destination
NOR source1 source2 destination
INPUT node1 node2 ... -1
OUTPUT node1 node2 ... -1
```

Node identifiers are nonnegative integers. Blank lines and ordinary whitespace are accepted. INPUT and OUTPUT declarations each occur once and preserve vector bit order; `-1` is a terminator, not a node. Input and output bits follow declaration order, not sorted node order.

The simulator first parses and validates the entire circuit, then computes a dependency order. Each simulation creates fresh node values, assigns the input bits, evaluates every gate once, and collects output bits. No state or delay modeling is needed for the gates in the supplied files.

Malformed records, unsupported gates, invalid vector lengths/content, missing drivers, duplicate drivers, and dependency cycles produce errors. A missing-file error means the circuit path is incorrect or the local circuit descriptions have not been supplied.
