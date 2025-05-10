#!/usr/bin/env python3
import sys
import networkx as nx
import matplotlib.pyplot as plt

def main():
    # Read adjacency matrix from stdin
    adj_matrix = []
    for line in sys.stdin:
        row = list(map(int, line.strip().split()))
        if row:
            adj_matrix.append(row)
    
    # Create graph
    G = nx.DiGraph()
    for i, row in enumerate(adj_matrix):
        for j, val in enumerate(row):
            if val == 1:
                G.add_edge(i, j)
    
    # Draw and save to file
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, 
           node_color='skyblue', 
           node_size=800,
           arrowsize=20)
    plt.title("DAG Visualization")
    plt.savefig('dag.png', dpi=300, bbox_inches='tight')
    print("DAG visualization saved to dag.png")

if __name__ == "__main__":
    main()
