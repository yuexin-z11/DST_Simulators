# Implementation milestones

Complete one milestone at a time and check its behavior before moving on.
The containers and queue algorithm below are implementation choices, not requirements imposed by the handout.

- [x] **1. Read declarations.** In `Circuit::read`, open the file, read lines, and extract whitespace-separated tokens. Store INPUT and OUTPUT IDs in their declared order, excluding the final -1. Verify the small fixture's inputs are 1, 2 and output is 4.
- [ ] **2. Read gates.** Store a Gate for each gate record, in file order. Verify the small fixture has INV (source 3, destination 4) and AND (sources 1, 2, destination 3). Return a Circuit so the parsing checkpoint can pass.
- [ ] **3. Validate the circuit.** Check file errors, declarations, supported gate names, pin counts, node IDs, unique drivers, and missing sources. Add focused checks for invalid files.
- [ ] **4. Implement gate logic.** Implement the six Boolean operations in `evaluate_gate`. Check every input combination using small circuits, including both unary operations.
- [ ] **5. Assign input values.** In `simulate`, reject wrong lengths and nonbinary characters. Use a fresh node-ID-to-bit dictionary for every call. Map vector bits to INPUT declaration order.
- [ ] **6. Execute with a queue.** Use gate indices in a ready queue, unresolved dependency counts, and node-to-consumer lists. Enqueue only gates whose source values are available. Execute, store the destination, and release newly ready consumers. Count distinct source dependencies so repeated fan-in works. Reject stalled/cyclic circuits and collect OUTPUT bits in declaration order.
- [ ] **7. Verify simulation.** Pass the starter checkpoints; add shuffled gate order, repeated fan-in, output ordering, multiple vectors, and cycle checks. Confirm the local .txt files are the intended .chat circuit descriptions. Cross-check results with an independent evaluator or another available reference.
- [ ] **8. Run the required cases.** Complete `run_required.cpp`; use exactly the 20 provided vectors. Regenerate results and create four clearly labeled tables. Preserve leading zeros.
- [ ] **9. Write the report.** Describe your actual data structures in at most one page and your algorithm using pseudocode or a flowchart in at most one page. Append the simulation tables. Check the rendered page lengths.
- [ ] **10. Prepare submission.** Confirm all 20 runs are recorded, check the course's submission instructions for filenames/source requirements, and review the final artifact. Due October 1, 2026. Commit or publish only when explicitly requested.
