import matplotlib.pyplot as plt
import networkx as nx
import numpy as np
import subprocess

# Step 1: Compile and run the C program to generate the DAG
def generate_dag(num_nodes=5, saturation=0.6):
    # Compile and run the C program (assuming it's named `dag_gen.c`)
    compile_cmd = f"gcc -o dag_gen dag_gen.c && ./dag_gen {num_nodes} {saturation}"
    subprocess.run(compile_cmd, shell=True, check=True)
    
    # Read the adjacency matrix from a file (or modify C program to print it)
    # For simplicity, we'll simulate the output here.
    # In practice, modify the C program to write the matrix to a file.
    adj_matrix = np.random.randint(0, 2, (num_nodes, num_nodes))
    np.fill_diagonal(adj_matrix, 0)  # Remove self-loops
    return adj_matrix

# Step 2: Visualize the DAG
def visualize_dag(adj_matrix):
    G = nx.DiGraph()
    num_nodes = adj_matrix.shape[0]
    G.add_nodes_from(range(num_nodes))
    
    # Add edges from the adjacency matrix
    for i in range(num_nodes):
        for j in range(num_nodes):
            if adj_matrix[i][j] == 1:
                G.add_edge(i, j)
    
    # Draw the DAG
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_color='skyblue', 
            node_size=800, arrowsize=20, font_weight='bold')
    plt.title("Generated DAG")
    plt.show()

# Example usage
if __name__ == "__main__":
    adj_matrix = generate_dag(num_nodes=5, saturation=0.6)
    visualize_dag(adj_matrix)
