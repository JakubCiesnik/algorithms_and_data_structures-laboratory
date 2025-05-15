# Graph Algorithms Benchmark – README

This project benchmarks the performance of graph algorithms (topological sort and Prim's MST) using two graph representations: adjacency matrix and adjacency list.

## Prerequisites

- GCC compiler (or compatible)
- Make
- Linux environment

## Project Structure

- `src/` – Source code for graph algorithms and benchmarks
- `results/` – Output CSV files with benchmark results
- `target/` – Compiled benchmark executables
- `Makefile` – Build and run instructions

## How to Build and Run Benchmarks

1. **Clone or download the repository and enter the project directory.**

2. **Build the project:**
   ```bash
   make clean
   make
   ```

3. **Run the Topological Sort benchmark:**
   ```bash
   make run_topo_benchmark
   ```
   - Output: `results/toposort_benchmark.csv`

4. **Run the Prim's MST benchmark:**
   ```bash
   make run_prim_benchmark
   ```
   - Output: `results/prim_benchmark_sat_30.csv` and `results/prim_benchmark_sat_70.csv`

5. **View results:**
   - Open the CSV files in the `results/` directory with your preferred spreadsheet tool or text editor.

## Notes

- You can adjust the number of nodes, saturation, or other parameters by editing the appropriate source files in `src/`.
- The `Makefile` ensures all necessary directories are created and all dependencies are built.
- If you encounter any issues, ensure you have write permissions for the `results/` and `target/` directories.