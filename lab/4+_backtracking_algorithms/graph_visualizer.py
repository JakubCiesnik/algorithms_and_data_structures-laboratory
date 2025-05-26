#!/usr/bin/env python3
"""
Simple Graph Visualizer
Just paste your adjacency matrix and get a PNG with cycle info
"""

import matplotlib.pyplot as plt
import networkx as nx
from itertools import permutations

def parse_matrix(input_text):
    """Parse matrix from input like '0 1 0\n1 0 1\n0 1 0'"""
    lines = input_text.strip().split('\n')
    matrix = []
    for line in lines:
        row = [int(x) for x in line.split()]
        matrix.append(row)
    return matrix

def is_eulerian(matrix):
    """Check if graph has Euler cycle"""
    n = len(matrix)
    
    # Check if connected (simple check - assume it is for small graphs)
    # Check degrees
    degrees = [sum(matrix[i]) for i in range(n)]
    odd_count = sum(1 for d in degrees if d % 2 == 1)
    
    return odd_count == 0

def has_hamilton_cycle(matrix):
    """Check Hamilton cycle for small graphs (brute force)"""
    n = len(matrix)
    if n < 3:
        return False
    if n > 8:  # Too big for brute force
        return "Unknown (too large)"
    
    # Try all permutations starting from vertex 0
    vertices = list(range(1, n))
    
    for perm in permutations(vertices):
        path = [0] + list(perm) + [0]
        
        # Check if path is valid
        valid = True
        for i in range(len(path) - 1):
            if matrix[path[i]][path[i + 1]] == 0:
                valid = False
                break
        
        if valid:
            return True
    
    return False

def visualize_graph(matrix, filename="graph.png"):
    """Create graph visualization"""
    n = len(matrix)
    
    # Create NetworkX graph
    G = nx.Graph()
    G.add_nodes_from(range(n))
    
    edge_count = 0
    for i in range(n):
        for j in range(i + 1, n):
            if matrix[i][j] == 1:
                G.add_edge(i, j)
                edge_count += 1
    
    # Check properties
    euler = is_eulerian(matrix)
    hamilton = has_hamilton_cycle(matrix)
    degrees = [sum(matrix[i]) for i in range(n)]
    
    # Create plot
    plt.figure(figsize=(10, 8))
    
    # Layout
    if n <= 6:
        pos = nx.circular_layout(G)
    else:
        pos = nx.spring_layout(G, k=1.5, iterations=50)
    
    # Draw graph
    nx.draw_networkx_nodes(G, pos, node_color='lightblue', node_size=800)
    nx.draw_networkx_edges(G, pos, width=2, alpha=0.7)
    nx.draw_networkx_labels(G, pos, font_size=14, font_weight='bold')
    
    # Add info text
    info = f"Vertices: {n}\n"
    info += f"Edges: {edge_count}\n"
    info += f"Degrees: {degrees}\n"
    info += f"Euler Cycle: {'YES' if euler else 'NO'}\n"
    info += f"Hamilton Cycle: {hamilton}"
    
    plt.text(0.02, 0.98, info, transform=plt.gca().transAxes, 
             verticalalignment='top', fontsize=12,
             bbox=dict(boxstyle='round', facecolor='yellow', alpha=0.8))
    
    plt.title("Graph Analysis", fontsize=16)
    plt.axis('off')
    plt.tight_layout()
    plt.savefig(filename, dpi=200, bbox_inches='tight')
    plt.close()
    
    print(f"Graph saved as {filename}")
    print(f"Euler cycle: {'YES' if euler else 'NO'}")
    print(f"Hamilton cycle: {hamilton}")

def main():
    print("=== Simple Graph Visualizer ===")
    print("Paste your adjacency matrix (each row on new line):")
    print("Example:")
    print("0 1 1")
    print("1 0 1") 
    print("1 1 0")
    print("\nEnter matrix (press Enter twice when done):")
    
    lines = []
    while True:
        line = input()
        if line.strip() == "":
            break
        lines.append(line)
    
    if not lines:
        print("No input provided!")
        return
    
    try:
        matrix = parse_matrix('\n'.join(lines))
        print(f"\nParsed {len(matrix)}x{len(matrix[0])} matrix")
        
        # Generate filename
        filename = f"graph_{len(matrix)}x{len(matrix)}.png"
        
        visualize_graph(matrix, filename)
        
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
