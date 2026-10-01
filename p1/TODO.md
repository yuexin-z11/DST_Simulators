# Project status

## Completed

- Parse declarations and gates from the supplied circuit descriptions.
- Evaluate all six gate operations and validate runtime input vectors.
- Schedule gates by dependencies, including repeated sources and arbitrary file order.
- Check truth tables, output order, fresh simulation state, and stalled dependencies.
- Run 20 benchmark vectors and export four tables plus CSV results.
- Export a data-structure summary and all four simulation tables in [report_tables.xlsx](report_tables.xlsx).

## Known limitations and next steps

- The four benchmark circuit descriptions are local inputs and are not included in this repository. A fresh checkout needs these files to run the batch benchmark.
- Confirm that each local `.txt` file matches the intended benchmark circuit variant.
- Add malformed-netlist validation if the parser will be used with untrusted circuit descriptions.

The parser currently assumes valid circuit syntax. The queue-based scheduler, containers, and export formats are implementation choices.
