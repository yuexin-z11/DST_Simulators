// Small CLI wrapper. Circuit parsing and simulation are your implementation tasks.
#include "circuit.hpp"

#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: simulator CIRCUIT_FILE INPUT_VECTOR [INPUT_VECTOR ...]\n";
        return 2;
    }
    try {
        const Circuit circuit = Circuit::read(argv[1]);
        std::cout << "Circuit\tInput vector\tOutput vector\n";
        for (int index = 2; index < argc; ++index) {
            const std::string output = circuit.simulate(argv[index]);
            std::cout << argv[1] << '\t' << argv[index] << '\t' << output << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
}
