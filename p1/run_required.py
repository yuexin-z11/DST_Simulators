"""Run all assignment vectors and save report tables beside this script."""

import csv
from pathlib import Path

from simulator import Circuit


VECTORS = {
    's27': ['1110101', '0001010', '1010101', '0110111', '1010001'],
    's298f_2': ['10101010101010101', '01011110000000111',
                '11111000001111000', '11100001110001100',
                '01111011110000000'],
    's344f_2': ['101010101010101011111111', '010111100000001110000000',
                '111110000011110001111111', '111000011100011000000000',
                '011110111100000001111111'],
}
VECTORS['s349f_2'] = VECTORS['s344f_2'][:]
ROOT = Path(__file__).resolve().parent


def main():
    rows = []
    for name, vectors in VECTORS.items():
        circuit = Circuit.read(ROOT / f'{name}.txt')
        for vector in vectors:
            rows.append((f'{name}.chat', vector, circuit.simulate(vector)))
    header = ['Circuit', 'Input vector', 'Output vector']
    with (ROOT / 'results.csv').open('w', newline='') as stream:
        writer = csv.writer(stream)
        writer.writerow(header)
        writer.writerows(rows)
    table = '\n'.join([
        '| ' + ' | '.join(header) + ' |',
        '|---|---|---|',
        *('| ' + ' | '.join(row) + ' |' for row in rows),
    ])
    (ROOT / 'results.md').write_text(
        '# Required simulation results\n\n'
        'Circuit names use the assignment’s `.chat` names; the supplied '
        'files have `.txt` extensions. Bits follow INPUT/OUTPUT declaration order.\n\n'
        + table + '\n')
    print(table)


if __name__ == '__main__':
    main()
