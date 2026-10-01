# DST Simulators

A C++17 simulator for combinational Boolean circuits. It parses node declarations and logic gates, evaluates binary input vectors, and reports output bits in declaration order. A dependency queue lets gates appear in any order in the circuit file. The project also includes a batch runner for four benchmark circuits and an [Excel results workbook](p1/report_tables.xlsx).

## Quick start

From the repository root, with `g++` (C++17) and GNU Make installed:

```bash
make -C p1
make -C p1 check
./p1/build/simulator p1/tests/small.net 11 10
```

The included example produces output `0` for input `11` and output `1` for input `10`. No external circuit files are needed for this example or the checks.

## Input and assumptions

Circuit files declare `INPUT` and `OUTPUT` node IDs ending in `-1`, followed or preceded by `INV`, `BUF`, `AND`, `OR`, `NAND`, or `NOR` gate records. Input vectors contain one `0` or `1` per declared input node. The simulator expects well-formed combinational circuits with one driver per gate destination and resolvable sources; it does not model timing or stored state.

The batch runner uses four local circuit descriptions that are not included in this repository. See the [detailed guide](p1/README.md) for the file syntax, batch file names, commands, outputs, and limitations. [Project status](p1/TODO.md) lists current follow-up work.
