# ECE 6140 Project 1

Requires Python 3.9 or newer; no third-party packages.

From `/mnt/d/ECE_6140`, simulate a circuit with one or more vectors:

```bash
python3 p1/simulator.py p1/s27.txt 1110101 0001010
```

The same parser accepts `.chat` paths. The original supplied `.txt` circuit files are preserved.

Run all 20 assignment cases and regenerate Markdown/CSV tables:

```bash
python3 p1/run_required.py
```

Run verification:

```bash
python3 -m unittest discover -s p1 -v
```

- `simulator.py`: parser, circuit representation, topological ordering, Boolean evaluation, CLI.
- `run_required.py`: required input vectors and table generation; contains no expected outputs.
- `test_simulator.py`: truth-table tests, validation, independent recursive reference checks.
- `REPORT.md`: concise data-structure explanation and algorithm/pseudocode, plus supporting verification notes.
- `results.md` and `results.csv`: all required input/output pairs.
- `../RESUME_SESSION.md`: instructions and status for continuing this work.

Input and output bits follow declaration order, not sorted node order. The simulator rejects unsupported syntax, invalid vector lengths/content, missing drivers, duplicate drivers, and dependency cycles. No state or delay modeling is needed for the gates in these files.
