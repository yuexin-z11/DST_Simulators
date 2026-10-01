# Build the CLI and batch runner, then run circuit regression checks.
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude

.PHONY: all check
all: build/simulator build/run_benchmarks

build:
	mkdir -p build

build/simulator: src/main.cpp src/circuit.cpp include/circuit.hpp | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/main.cpp src/circuit.cpp -o $@

build/run_benchmarks: src/run_benchmarks.cpp src/circuit.cpp include/circuit.hpp | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/run_benchmarks.cpp src/circuit.cpp -o $@

build/test_circuit: tests/test_circuit.cpp src/circuit.cpp include/circuit.hpp | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests/test_circuit.cpp src/circuit.cpp -o $@

check: build/test_circuit
	./build/test_circuit tests/small.net
