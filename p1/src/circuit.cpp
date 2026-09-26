// Implement circuit loading, Boolean logic, and queue scheduling here.
#include "circuit.hpp"

#include <stdexcept>

Circuit Circuit::read(const std::string& path) {
    // Milestones 1-3: open the file, parse records, and validate connectivity.
    // Use getline for complete lines and istringstream for whitespace tokens.
    // Collect gates in file order; this is not necessarily execution order.
    (void)path;  // Remove when the parameter is used by your implementation.
    throw std::logic_error("TODO: implement Circuit::read");
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
