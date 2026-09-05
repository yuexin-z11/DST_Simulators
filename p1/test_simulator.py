"""Truth tables, validation, and an independent recursive reference evaluator."""

from functools import lru_cache
from itertools import product
import random
import tempfile
import unittest
from pathlib import Path

from run_required import ROOT, VECTORS
from simulator import Circuit


def reference(path, vector):
    # Parse separately, evaluate on demand, and use explicit truth tables.
    drivers = {}
    for line in path.read_text().splitlines():
        tokens = line.split()
        if not tokens:
            continue
        kind, *pins = tokens
        if kind == 'INPUT':
            inputs = pins[:-1]
        elif kind == 'OUTPUT':
            outputs = pins[:-1]
        else:
            drivers[pins[-1]] = (kind, pins[:-1])
    assigned = dict(zip(inputs, vector))
    tables = {'INV': '10', 'BUF': '01', 'AND': '0001',
              'OR': '0111', 'NAND': '1110', 'NOR': '1000'}

    @lru_cache(None)
    def evaluate(node):
        if node in assigned:
            return assigned[node]
        kind, sources = drivers[node]
        index = int(''.join(evaluate(source) for source in sources), 2)
        return tables[kind][index]

    return ''.join(evaluate(node) for node in outputs)


class SimulatorTests(unittest.TestCase):
    def parse(self, text):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / 'test.chat'
            path.write_text(text)
            return Circuit.read(path)

    def test_truth_tables_and_output_order(self):
        circuit = self.parse('INV 1 3\nBUF 1 4\nAND 1 2 5\nOR 1 2 6\n'
                             'NAND 1 2 7\nNOR 1 2 8\nINPUT 1 2 -1\n'
                             'OUTPUT 8 7 6 5 4 3 -1\n')
        expected = {'00': '110001', '01': '011001',
                    '10': '011010', '11': '001110'}
        for vector, output in expected.items():
            self.assertEqual(circuit.simulate(vector), output)

    def test_dependencies_repeated_fanin_and_fresh_values(self):
        circuit = self.parse('AND 3 3 4\nINV 8 3\nINPUT 8 -1\nOUTPUT 4 8 -1\n')
        for vector, expected in [('0', '10'), ('1', '01'), ('0', '10')]:
            self.assertEqual(circuit.simulate(vector), expected)

    def test_invalid_netlists(self):
        cases = [
            'BUF 9 2\nINPUT 1 -1\nOUTPUT 2 -1',
            'BUF 3 2\nBUF 2 3\nINPUT 1 -1\nOUTPUT 2 -1',
            'BUF 1 2\nINV 1 2\nINPUT 1 -1\nOUTPUT 2 -1',
            'BUF 2 1\nINPUT 1 -1\nOUTPUT 1 -1',
            'XOR 1 1 2\nINPUT 1 -1\nOUTPUT 2 -1',
            'INV 1 2 3\nINPUT 1 -1\nOUTPUT 3 -1',
            'INPUT 1\nOUTPUT 1 -1',
            'INPUT 1 1 -1\nOUTPUT 1 -1',
            'INPUT 1 -1\nINPUT 2 -1\nOUTPUT 1 -1',
            'INPUT 1 -1',
        ]
        for text in cases:
            with self.subTest(text=text), self.assertRaises(ValueError):
                self.parse(text)

    def test_invalid_vectors(self):
        circuit = self.parse('INPUT 1 -1\nOUTPUT 1 -1')
        for vector in ['', '00', 'x', '2']:
            with self.assertRaises(ValueError):
                circuit.simulate(vector)

    def test_reference_comparison(self):
        rng = random.Random(6140)
        for name, required in VECTORS.items():
            path = ROOT / f'{name}.txt'
            circuit = Circuit.read(path)
            if name == 's27':
                extra = [''.join(bits) for bits in product('01', repeat=7)]
            else:
                extra = ['0' * len(circuit.inputs), '1' * len(circuit.inputs)]
                extra += [''.join(rng.choice('01') for _ in circuit.inputs)
                          for _ in range(1000)]
            for vector in required + extra:
                with self.subTest(circuit=name, vector=vector):
                    self.assertEqual(circuit.simulate(vector), reference(path, vector))
            # File order must not affect connectivity or bit ordering.
            shuffled = list(circuit.gates)
            rng.shuffle(shuffled)
            reordered = Circuit(circuit.inputs, circuit.outputs, shuffled)
            for vector in required:
                self.assertEqual(circuit.simulate(vector), reordered.simulate(vector))


if __name__ == '__main__':
    unittest.main()
