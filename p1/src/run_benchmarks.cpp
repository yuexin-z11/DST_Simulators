// Run the benchmark vectors and export four Markdown tables plus a CSV table.
#include "circuit.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Pair a circuit basename with its five input vectors in benchmark order.
struct Benchmark {
    std::string name;
    std::vector<std::string> vectors;
};

// Strings preserve leading zeros and keep the benchmark vectors in a stable order.
const std::vector<Benchmark> benchmarks = {
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
    if (argc != 2) {
        std::cerr << "Usage: run_benchmarks CIRCUIT_DIRECTORY\n";
        return 2;
    }
    try {
        const std::filesystem::path directory(argv[1]);
        // Complete every simulation in memory before replacing existing results.
        std::ostringstream markdown;
        std::ostringstream csv;
        markdown << "# Benchmark simulation results\n\n"
                 << "Bits follow INPUT and OUTPUT declaration order.\n\n";
        csv << "Circuit,Input vector,Output vector\n";

        for (const Benchmark& benchmark : benchmarks) {
            // Supplied descriptions use .txt; table labels use the same filename.
            const std::string filename = benchmark.name + ".txt";
            const Circuit circuit = Circuit::read((directory / filename).string());
            markdown << "## " << filename << "\n\n"
                     << "| Input vector | Output vector |\n"
                     << "|---|---|\n";
            for (const std::string& input : benchmark.vectors) {
                const std::string output = circuit.simulate(input);
                markdown << "| " << input << " | " << output << " |\n";
                // These fields contain only fixed filenames and binary digits.
                csv << filename << ',' << input << ',' << output << '\n';
            }
            markdown << '\n';
        }

        // Write results beside the supplied circuits; reruns overwrite these files.
        std::ofstream markdown_file(directory / "results.md");
        std::ofstream csv_file(directory / "results.csv");
        if (!markdown_file || !csv_file) {
            throw std::runtime_error("Cannot open result files in " + directory.string());
        }
        markdown_file << markdown.str();
        csv_file << csv.str();
        markdown_file.close();
        csv_file.close();
        if (!markdown_file || !csv_file) {
            throw std::runtime_error("Failed to write result files");
        }
        std::cout << markdown.str();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
}
