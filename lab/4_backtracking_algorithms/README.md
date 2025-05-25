# Backtracking Algorithms Laboratory

This project benchmarks and analyzes algorithms for finding Eulerian and Hamiltonian cycles in undirected graphs using adjacency matrix representation.

## Features
- **Graph Representation:** Adjacency matrix (macierz sąsiedztwa)
- **Graph Generation:**
  - Generates two connected, undirected graphs for each n:
    - One with 30% edge density (sparse)
    - One with 70% edge density (dense)
  - All generated graphs are both Eulerian (all degrees even, connected) and Hamiltonian (contain a Hamiltonian cycle)
- **Algorithms:**
  - **Algorithm A:** Hierholzer’s algorithm for finding an Eulerian cycle
  - **Algorithm B:** Backtracking algorithm for finding a Hamiltonian cycle
- **Benchmarking:**
  - Measures execution time of both algorithms for 15 values of n (from 100 to 800, step 50)
  - Results are saved to `results.csv` for plotting

## File Structure
- `src/def_graph.c`, `def_graph.h`: Basic graph structure and utilities
- `src/euler_check.c`, `euler_check.h`: Eulerian cycle algorithm and helpers
- `src/hamilton_check.c`, `hamilton_check.h`: Hamiltonian cycle algorithm and helpers
- `src/graph_generator.c`, `graph_generator.h`: Random graph generation (Eulerian & Hamiltonian, with density)
- `src/test_graph.c`: Main benchmarking program
- `results.csv`: Output file with timing results
- `Makefile`: Build and run automation

## Build & Run
1. **Build:**
   ```sh
   make
   ```
2. **Run :**
   ```sh
   make run
   ```

## Output
- Results are written to `results.csv` in the format:
  ```
  n,density,euler_time,hamilton_time
  100,sparse,0.00001,0.00002
  ...
  ```
- Use your favorite plotting tool (e.g., Python/matplotlib, Excel) to visualize:
  - **Plot 1:** t = f(n) for both algorithms, 30% density
  - **Plot 2:** t = f(n) for both algorithms, 70% density

## Complexity Classes
- **Eulerian Cycle:** Polynomial time (Hierholzer’s algorithm, O(E))
- **Hamiltonian Cycle:** NP-complete (exponential time, backtracking)

## Observations
- **Eulerian cycle algorithm** is fast even for large, dense graphs.
- **Hamiltonian cycle algorithm** becomes infeasible for large n due to exponential complexity; practical only for small graphs.
- **Edge density**: Higher density may slightly affect Eulerian cycle time, but Hamiltonian cycle time is dominated by n.
