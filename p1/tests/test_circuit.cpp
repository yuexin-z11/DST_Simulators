// Check parsing, Boolean truth tables, input validation, and queue scheduling.
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
        // Exercise every input combination through the public simulation API.
        const std::vector<std::string> kinds = {"INV", "BUF", "AND", "OR", "NAND", "NOR"};
        const std::vector<std::string> truth = {"10", "01", "0001", "0111", "1110", "1000"};
        for (std::size_t k = 0; k < kinds.size(); ++k) {
            const bool unary = k < 2;
            Circuit single;
            single.inputs = unary ? std::vector<int>{7} : std::vector<int>{7, 19};
            single.outputs = {30};
            single.gates = {{kinds[k], single.inputs, 30}};
            for (std::size_t bits = 0; bits < truth[k].size(); ++bits) {
                std::string vector;
                if (!unary) vector.push_back(static_cast<char>('0' + bits / 2));
                vector.push_back(static_cast<char>('0' + bits % 2));
                if (single.simulate(vector) != std::string(1, truth[k][bits])) {
                    throw std::runtime_error("Truth table failed: " + kinds[k]);
                }
            }
        }
        // Runtime vectors must have the correct length and binary characters.
        for (const auto& vector : {"", "1", "111", "1x"}) {
            bool rejected = false;
            try { circuit.simulate(vector); }
            catch (const std::invalid_argument&) { rejected = true; }
            if (!rejected) throw std::runtime_error("Invalid vector accepted");
        }
        std::cout << "Truth-table and input-validation checks passed\n";
        // Exercise repeated fan-in, branching consumers, and output ordering.
        // Both consumers precede the gate producing their shared source.
        Circuit shared;
        shared.inputs = {8};
        shared.outputs = {30, 8, 20};
        shared.gates = {{"AND", {10, 10}, 20},
                        {"INV", {10}, 30}, {"BUF", {8}, 10}};
        if (shared.simulate("1") != "011" ||
            shared.simulate("0") != "100" ||
            shared.simulate("1") != "011") {
            throw std::runtime_error("Dependency and output-order check failed");
        }

        // A dependency cycle must stop with an error instead of partial output.
        Circuit cyclic;
        cyclic.outputs = {1};
        cyclic.gates = {{"INV", {2}, 1}, {"INV", {1}, 2}};
        bool rejected = false;
        try {
            cyclic.simulate("");
        } catch (const std::logic_error& error) {
            rejected = std::string(error.what()) ==
                "Cannot evaluate circuit: cycle or missing source";
        }
        if (!rejected) throw std::runtime_error("Cycle check failed");
        std::cout << "Scheduling checks passed\n";
    } catch (const std::exception& error) {
        std::cerr << "Check failed: " << error.what() << '\n';
        return 1;
    }
}
