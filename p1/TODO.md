# Project status

## Completed

- Parse declarations and gates from the supplied circuit descriptions.
- Evaluate all six gate operations and validate runtime input vectors.
- Schedule gates by dependencies, including repeated sources and arbitrary file order.
- Check truth tables, output order, fresh simulation state, and stalled dependencies.
- Run 20 benchmark vectors and export four tables plus CSV results.
- Write the data-structure explanation, algorithm pseudocode, and simulation tables in [REPORT.md](REPORT.md).

## Known limitations and next steps

- The four benchmark circuit descriptions are local inputs and are not included in this repository. A fresh checkout needs these files to run the batch benchmark.
- Confirm that each local `.txt` file matches the circuit identified by its `.chat` table label in the report.
- Add malformed-netlist validation if the parser will be used with untrusted circuit descriptions.

The parser currently assumes valid circuit syntax. The queue-based scheduler, containers, and export formats are implementation choices documented in the report.
