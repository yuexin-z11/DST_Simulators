#pragma once

// Public data model and interfaces. Function bodies belong in circuit.cpp.
#include <string>
#include <unordered_map>
#include <vector>

// A gate consumes source node values and produces one destination node value.
// Node IDs identify wires; they are not positions in an input vector.
struct Gate {
    std::string kind;
    std::vector<int> sources;
    int destination;
};

class Circuit {
public:
    // Preserve declaration order when assigning inputs and collecting outputs.
    std::vector<int> inputs;
    std::vector<int> outputs;
    std::vector<Gate> gates;

    // Parse a local circuit description, assuming valid supplied file syntax.
    static Circuit read(const std::string& path);

    // Evaluate one vector using a queue of gates whose sources are available.
    // Each call must create fresh values and scheduling information.
    std::string simulate(const std::string& input_vector) const;

private:
    // Apply one supported Boolean operation to already available source values.
    static int evaluate_gate(const Gate& gate, const std::unordered_map<int, int>& values);
};
