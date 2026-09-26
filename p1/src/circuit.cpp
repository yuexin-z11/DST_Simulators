#include "circuit.hpp"

#include <fstream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

Circuit Circuit::read(const std::string& path) {
    // read declarations and gate records, assuming valid supplied file syntax
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
        // first token identifies the gate operation.
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
        // with one source node
        else if (keyword == "INV" || keyword == "BUF"){
            ss >> source1 >> gate.destination;
            gate.sources.push_back(source1);
            circuit.gates.push_back(gate);
        }
        // with two source nodes
        else if (keyword == "AND" || keyword == "OR" || keyword == "NAND" || keyword == "NOR"){
            ss >> source1 >> source2 >> gate.destination;
            gate.sources.push_back(source1);
            gate.sources.push_back(source2);
            circuit.gates.push_back(gate);
        }
    }

    return circuit;
}

int Circuit::evaluate_gate(const Gate& gate, const std::unordered_map<int, int>& values) {
    // get the bit value at the first source node
    const int a = values.at(gate.sources[0]);

    // unary gates have only one source; handle them before reading source 2.
    if (gate.kind == "INV") return !a;
    if (gate.kind == "BUF") return a;

    // read the bit value at the second source node
    const int b = values.at(gate.sources[1]);
    // logical operators produce 0 or 1. NAND and NOR invert AND and OR.
    if (gate.kind == "AND") return a && b;
    if (gate.kind == "OR") return a || b;
    if (gate.kind == "NAND") return !(a && b);
    if (gate.kind == "NOR") return !(a || b);
    // Supplied circuits use only the six supported operations.
    throw std::logic_error("Unsupported gate operation: " + gate.kind);
}

std::string Circuit::simulate(const std::string& input_vector) const {
    // Check runtime vector length before indexing its characters.
    if (input_vector.size() != inputs.size()) {
        throw std::invalid_argument("Input vector length must match the number of inputs");
    }
    // check input characters
    if (input_vector.find_first_not_of("01") != std::string::npos) {
        // Reject a vector containing any character other than a binary digit.
        throw std::invalid_argument("Input vector must contain only 0 and 1");
    }

    // Start a fresh node-value map and convert binary characters to integer bits.
    std::unordered_map<int, int> values;
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        values[inputs[i]] = input_vector[i] - '0';
    }

    // store indices of gates whose source values are all available
    std::queue<std::size_t> ready;
    // create one unresolved-source counter per gate, initially zero.
    std::vector<std::size_t> missing(gates.size(), 0);
    // Map each unavailable source node to the gates waiting for its value.
    std::unordered_map<int, std::vector<std::size_t>> consumers;

    // build dependency information for each gate
    for (std::size_t i = 0; i < gates.size(); ++i) {
        // repeated source (AND 3 3 4) has only one dependency.
        const std::unordered_set<int> sources(gates[i].sources.begin(), gates[i].sources.end());

        // Inspect each distinct source node required by this gate.
        for (int source : sources) {
            if (values.find(source) == values.end()) {
                ++missing[i];
                // register gate i to be notified when this source gets a value.
                consumers[source].push_back(i);
            }
        }

        if (missing[i] == 0) ready.push(i);
    }

    // count evaluated gates so an unfinished dependency chain can be detected.
    std::size_t executed = 0;

    while (!ready.empty()) {
        const std::size_t index = ready.front();

        ready.pop();
        const Gate& gate = gates[index];
        // compute the gate bit and store it at the destination node
        values[gate.destination] = evaluate_gate(gate, values);
        ++executed;

        // look for gates waiting on the node just produced
        const auto waiting = consumers.find(gate.destination);
        if (waiting != consumers.end()) {
            for (std::size_t consumer : waiting->second) {
                if (--missing[consumer] == 0) ready.push(consumer);
            }
        }
    }

    // detect a stalled queue before trying to collect incomplete output values.
    if (executed != gates.size()) {
        throw std::logic_error("Cannot evaluate circuit: cycle or missing source");
    }

    // create the output bit string
    std::string result;
    result.reserve(outputs.size());

    // visit output node IDs in their declared order
    for (int output : outputs) {
        result.push_back(static_cast<char>('0' + values.at(output)));
    }

    return result;
}
