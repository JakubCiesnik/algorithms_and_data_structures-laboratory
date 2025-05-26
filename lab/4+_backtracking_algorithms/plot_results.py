import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

def plot_results():
    # Read results
    results_file = 'results/task1_results.csv'
    if not os.path.exists(results_file):
        print(f"Results file {results_file} not found. Please run the main program first.")
        return
    
    df = pd.read_csv(results_file)
    
    # Create two plots as requested
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
    
    # Plot 1: Algorithms A and B for 30% density
    ax1.plot(df['vertices'], df['euler_sparse_time'], 'b-o', label='Euler Cycle (30%)', linewidth=2)
    ax1.plot(df['vertices'], df['hamilton_sparse_time'], 'r-s', label='Hamilton Cycle (30%)', linewidth=2)
    ax1.set_xlabel('Number of Vertices (n)')
    ax1.set_ylabel('Execution Time (seconds)')
    ax1.set_title('Algorithm Performance - Sparse Graphs (30% density)')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.set_yscale('log')  # Log scale for better visualization
    
    # Plot 2: Algorithms A and B for 70% density
    ax2.plot(df['vertices'], df['euler_dense_time'], 'b-o', label='Euler Cycle (70%)', linewidth=2)
    ax2.plot(df['vertices'], df['hamilton_dense_time'], 'r-s', label='Hamilton Cycle (70%)', linewidth=2)
    ax2.set_xlabel('Number of Vertices (n)')
    ax2.set_ylabel('Execution Time (seconds)')
    ax2.set_title('Algorithm Performance - Dense Graphs (70% density)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    ax2.set_yscale('log')  # Log scale for better visualization
    
    plt.tight_layout()
    plt.savefig('results/task1_performance_plots.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    # Print statistics
    print("=== Performance Analysis ===")
    print(f"Average Euler time (30%): {df['euler_sparse_time'].mean():.6f} seconds")
    print(f"Average Hamilton time (30%): {df['hamilton_sparse_time'].mean():.6f} seconds")
    print(f"Average Euler time (70%): {df['euler_dense_time'].mean():.6f} seconds")
    print(f"Average Hamilton time (70%): {df['hamilton_dense_time'].mean():.6f} seconds")

if __name__ == "__main__":
    plot_results()
