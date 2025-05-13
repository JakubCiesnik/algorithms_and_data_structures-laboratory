#!/usr/bin/env python3
import sys
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
import numpy as np

def visualize_large_dag():
    adj_matrix = []
    node_count = 0
    
    # Read matrix and count nodes
    for line in sys.stdin:
        row = list(map(int, line.strip().split()))
        if row:
            adj_matrix.append(row)
            node_count += 1

    # Create graph using sparse representation
    G = nx.DiGraph()
    edge_list = []
    
    for i in range(node_count):
        for j in range(node_count):
            if adj_matrix[i][j]:
                edge_list.append((i, j))
    
    G.add_edges_from(edge_list)

    # Use efficient spring layout
    pos = nx.spring_layout(G, k=10/np.sqrt(node_count), iterations=50)
    
    # Optimized drawing
    plt.figure(figsize=(20, 20), dpi=50)
    nx.draw_networkx_nodes(G, pos, node_size=5000/node_count, 
                         node_color='skyblue', alpha=0.6)
    
    # Draw edges in batches
    nx.draw_networkx_edges(G, pos, edgelist=edge_list,
                          width=0.5, alpha=0.2,
                          arrowsize=5, arrowstyle='->')
    
    # Only draw labels for small graphs
    if node_count <= 200:
        nx.draw_networkx_labels(G, pos, font_size=6)
    
    plt.title(f"DAG Visualization ({node_count} nodes)")
    plt.savefig('large_dag.png', bbox_inches='tight')
    print(f"Visualization saved to large_dag.png")

if __name__ == "__main__":
    visualize_large_dag()
