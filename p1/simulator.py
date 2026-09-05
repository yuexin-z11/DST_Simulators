"""Boolean simulation of the supplied CHAT netlist format (Python 3)."""

import argparse
from collections import defaultdict, deque
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class Gate:
    kind: str
    fanin: tuple[int, ...]
    output: int


class Circuit:
    def __init__(self, inputs, outputs, gates):
        self.inputs = tuple(inputs)
        self.outputs = tuple(outputs)
        self.gates = tuple(gates)
        self.order = self._topological_order()

    @classmethod
    def read(cls, path):
        """Parse input pins first, destination last; -1 ends I/O declarations."""
        declarations = {}
        gates = []
        arity = {'INV': 1, 'BUF': 1, 'AND': 2, 'OR': 2,
                 'NAND': 2, 'NOR': 2}
        for number, line in enumerate(Path(path).read_text().splitlines(), 1):
            fields = line.split()
            if not fields:
                continue
            kind = fields[0]
            try:
                nodes = [int(token) for token in fields[1:]]
                if kind in ('INPUT', 'OUTPUT'):
                    if kind in declarations:
                        raise ValueError(f'duplicate {kind} declaration')
                    if len(nodes) < 2 or nodes[-1] != -1:
                        raise ValueError('I/O declaration must end with -1')
                    pins = nodes[:-1]
                    if any(n < 0 for n in pins) or len(set(pins)) != len(pins):
                        raise ValueError('invalid or duplicate I/O node')
                    declarations[kind] = pins
                else:
                    if kind not in arity:
                        raise ValueError(f'unsupported gate {kind}')
                    if len(nodes) != arity[kind] + 1 or any(n < 0 for n in nodes):
                        raise ValueError(f'invalid nodes for {kind}')
                    gates.append(Gate(kind, tuple(nodes[:-1]), nodes[-1]))
            except ValueError as error:
                raise ValueError(f'{path}:{number}: {error}') from error
        if set(declarations) != {'INPUT', 'OUTPUT'}:
            raise ValueError('both INPUT and OUTPUT declarations are required')
        return cls(declarations['INPUT'], declarations['OUTPUT'], gates)

    def _topological_order(self):
        drivers = {}
        primary = set(self.inputs)
        for gate in self.gates:
            if gate.output in primary or gate.output in drivers:
                raise ValueError(f'multiple drivers for node {gate.output}')
            drivers[gate.output] = gate
        known = primary | drivers.keys()
        referenced = set(self.outputs)
        for gate in self.gates:
            referenced.update(gate.fanin)
        if referenced - known:
            raise ValueError(f'undriven nodes: {sorted(referenced - known)}')

        # Count distinct gate-produced dependencies; primary inputs are ready.
        waiting = {}
        consumers = defaultdict(list)
        for gate in self.gates:
            dependencies = set(gate.fanin) - primary
            waiting[gate.output] = len(dependencies)
            for node in dependencies:
                consumers[node].append(gate.output)
        ready = deque(n for n, count in waiting.items() if count == 0)
        order = []
        while ready:
            node = ready.popleft()
            order.append(drivers[node])
            for destination in consumers[node]:
                waiting[destination] -= 1
                if waiting[destination] == 0:
                    ready.append(destination)
        if len(order) != len(self.gates):
            raise ValueError('circuit contains a dependency cycle')
        return tuple(order)

    def simulate(self, vector):
        if len(vector) != len(self.inputs) or set(vector) - {'0', '1'}:
            raise ValueError(f'expected exactly {len(self.inputs)} binary digits')
        values = dict(zip(self.inputs, map(int, vector)))
        for gate in self.order:
            bits = [values[node] for node in gate.fanin]
            if gate.kind == 'BUF':
                result = bits[0]
            elif gate.kind == 'INV':
                result = 1 - bits[0]
            elif gate.kind in ('AND', 'NAND'):
                result = int(all(bits))
                if gate.kind == 'NAND':
                    result = 1 - result
            else:  # OR or NOR; parser rejects all other gate names.
                result = int(any(bits))
                if gate.kind == 'NOR':
                    result = 1 - result
            values[gate.output] = result
        return ''.join(str(values[node]) for node in self.outputs)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('circuit', type=Path)
    parser.add_argument('vectors', nargs='+')
    args = parser.parse_args()
    try:
        circuit = Circuit.read(args.circuit)
        rows = [(v, circuit.simulate(v)) for v in args.vectors]
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')
    print('Circuit\tInput vector\tOutput vector')
    for vector, output in rows:
        print(f'{args.circuit.name}\t{vector}\t{output}')


if __name__ == '__main__':
    main()
