// Initial checkpoints. Expand these as each milestone is completed.
#include "circuit.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: test_circuit SMALL_CIRCUIT_FILE\n";
        return 2;
    }
    try {
        const Circuit circuit = Circuit::read(argv[1]);
        if (circuit.inputs != std::vector<int>{1, 2} ||
            circuit.outputs != std::vector<int>{4} || circuit.gates.size() != 2) {
            throw std::runtime_error("Small-circuit parsing check failed");
        }
        std::cout << "Parsing checkpoint passed\n";
        // File order puts INV before its source-producing AND gate.
        if (circuit.simulate("11") != "0" || circuit.simulate("10") != "1" ||
            circuit.simulate("11") != "0") {
            throw std::runtime_error("Simulation checkpoint failed");
        }
        std::cout << "Simulation checkpoint passed\n";
    } catch (const std::exception& error) {
        std::cerr << "Check failed: " << error.what() << '\n';
        return 1;
    }
}
