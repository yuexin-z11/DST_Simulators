// Implement circuit loading, Boolean logic, and queue scheduling here.
#include "circuit.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

Circuit Circuit::read(const std::string& path) {
    // Read declarations and gate records; full validation comes next.
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open circuit file: " + path);
    }

    Circuit circuit;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string keyword;
        ss >> keyword;
        Gate gate;
        // The first token identifies the gate operation.
        gate.kind = keyword;
        int source1, source2;

        if (keyword == "INPUT" || keyword == "OUTPUT") {
            // keep declaration order and exclude the -1 terminator.
            auto& nodes = (keyword == "INPUT")
                              ? circuit.inputs
                              : circuit.outputs;
            int node;
            while (ss >> node && node != -1) {
                nodes.push_back(node);
            }
        }
        else if (keyword == "INV" || keyword == "BUF"){
            ss >> source1 >> gate.destination;
            gate.sources.push_back(source1);
            circuit.gates.push_back(gate);
        }
        else if (keyword == "AND" || keyword == "OR" || keyword == "NAND" || keyword == "NOR"){
            ss >> source1 >> source2 >> gate.destination;
            gate.sources.push_back(source1);
            gate.sources.push_back(source2);
            circuit.gates.push_back(gate);
        }
    }

    return circuit;
}

int Circuit::evaluate_gate(const Gate& gate,
                           const std::unordered_map<int, int>& values) {
    // Milestone 4: implement INV, BUF, AND, OR, NAND, and NOR.
    (void)gate;
    (void)values;
    throw std::logic_error("TODO: implement Circuit::evaluate_gate");
}

std::string Circuit::simulate(const std::string& input_vector) const {
    // Milestones 5-6: validate the vector and assign primary input values.
    // Track unresolved gate sources and consumers of each node.
    // Queue gate indices only when all of their sources are ready.
    // After executing a gate, make newly ready consumers eligible.
    // Detect unfinished gates, then collect outputs in declaration order.
    (void)input_vector;
    throw std::logic_error("TODO: implement Circuit::simulate");
}
