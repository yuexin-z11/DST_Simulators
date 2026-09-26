// Batch-runner starter. These vectors come from the supplied assignment text.
#include "circuit.hpp"

#include <iostream>
#include <string>
#include <vector>

struct Benchmark {
    std::string name;
    std::vector<std::string> vectors;
};

// Strings preserve leading zeros. Keep the handout's order.
[[maybe_unused]] const std::vector<Benchmark> benchmarks = {
    {"s27", {"1110101", "0001010", "1010101", "0110111", "1010001"}},
    {"s298f_2", {"10101010101010101", "01011110000000111",
                 "11111000001111000", "11100001110001100",
                 "01111011110000000"}},
    {"s344f_2", {"101010101010101011111111", "010111100000001110000000",
                 "111110000011110001111111", "111000011100011000000000",
                 "011110111100000001111111"}},
    {"s349f_2", {"101010101010101011111111", "010111100000001110000000",
                 "111110000011110001111111", "111000011100011000000000",
                 "011110111100000001111111"}},
};

int main(int argc, char* argv[]) {
    // Milestone 8: accept a circuit directory, load each circuit, run its
    // five vectors, and write four input/output tables. Match filenames to
    // the supplied files; currently the local copies have .txt extensions.
    (void)argc;
    (void)argv;
    std::cerr << "TODO: implement the 20-case batch runner\n";
    return 1;
}
