#include "prim_mst.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h> // For INT_MAX

#define INF INT_MAX

// --- Prim's for Adjacency Matrix ---
MSTEdge* prim_mst_matrix(Graph* graph, int* mst_edge_count) {
    if (!graph || graph->is_directed || !graph->is_weighted || graph->num_nodes == 0) {
        fprintf(stderr, "Prim's MST requires a connected, undirected, weighted graph.\n");
        *mst_edge_count = 0;
        return NULL;
    }

    int num_nodes = graph->num_nodes;
    int* key = (int*)malloc(num_nodes * sizeof(int)); // Key values used to pick minimum weight edge
    int* parent = (int*)malloc(num_nodes * sizeof(int)); // Array to store constructed MST
    bool* in_mst = (bool*)malloc(num_nodes * sizeof(bool)); // To track vertices included in MST

    if (!key || !parent || !in_mst) {
        free(key); free(parent); free(in_mst);
        fprintf(stderr, "Memory allocation failed for Prim's (matrix).\n");
        *mst_edge_count = 0;
        return NULL;
    }

    for (int i = 0; i < num_nodes; i++) {
        key[i] = INF;
        in_mst[i] = false;
        parent[i] = -1;
    }

    key[0] = 0; // Start with the first vertex

    MSTEdge* mst_result = (MSTEdge*)malloc((num_nodes -1) * sizeof(MSTEdge));
    if (!mst_result && num_nodes > 1) {
         free(key); free(parent); free(in_mst);
         fprintf(stderr, "Memory allocation failed for MST result array.\n");
        *mst_edge_count = 0;
        return NULL;
    }
    *mst_edge_count = 0;

    for (int count = 0; count < num_nodes; count++) { // Iterate num_nodes times
        int u = -1;
        int min_key = INF;

        // Pick the minimum key vertex from the set of vertices not yet included in MST
        for (int v_idx = 0; v_idx < num_nodes; v_idx++) {
            if (!in_mst[v_idx] && key[v_idx] < min_key) {
                min_key = key[v_idx];
                u = v_idx;
            }
        }
        
        if (u == -1) { // Graph might not be connected if we can't find a next vertex
            // This check is important if graph connectivity isn't guaranteed by generator
            // For this exercise, generator aims for connected.
            // If count < num_nodes-1 and u == -1, it implies disconnected.
            break; 
        }

        in_mst[u] = true;

        // Add to MST result if it's not the first node (which has no parent in this context)
        if (parent[u] != -1) {
            mst_result[*mst_edge_count].u = parent[u];
            mst_result[*mst_edge_count].v = u;
            mst_result[*mst_edge_count].weight = graph->adj_matrix[parent[u]][u]; // or key[u]
            (*mst_edge_count)++;
        }


        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < num_nodes; v++) {
            if (graph->adj_matrix[u][v] != 0 && !in_mst[v] && graph->adj_matrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph->adj_matrix[u][v];
            }
        }
    }
    
    // Check if MST is fully formed (for connected graph)
    if (num_nodes > 0 && *mst_edge_count < num_nodes - 1) {
        // This might indicate a disconnected graph if generator didn't ensure connectivity
        // Or an issue with Prim's logic if it terminates early.
        // For this setup, we assume generator makes connected graph.
        // If not, the MST might be for a component.
    }


    free(key);
    free(parent);
    free(in_mst);

    if (num_nodes > 0 && *mst_edge_count == 0 && num_nodes > 1) { // No edges in MST for multi-node graph
        free(mst_result);
        return NULL; // Could indicate disconnected or single node
    }
    if (num_nodes == 0 || (num_nodes == 1 && *mst_edge_count == 0)) {
        free(mst_result); // No edges for 0 or 1 node graph
        return NULL;
    }


    return mst_result;
}

// --- Prim's for Adjacency List ---
MSTEdge* prim_mst_list(Graph* graph, int* mst_edge_count) {
    if (!graph || graph->is_directed || !graph->is_weighted || graph->num_nodes == 0) {
        fprintf(stderr, "Prim's MST requires a connected, undirected, weighted graph.\n");
        *mst_edge_count = 0;
        return NULL;
    }

    int num_nodes = graph->num_nodes;
    int* key = (int*)malloc(num_nodes * sizeof(int));
    int* parent = (int*)malloc(num_nodes * sizeof(int));
    bool* in_mst = (bool*)malloc(num_nodes * sizeof(bool));

    if (!key || !parent || !in_mst) {
        free(key); free(parent); free(in_mst);
        fprintf(stderr, "Memory allocation failed for Prim's (list).\n");
        *mst_edge_count = 0;
        return NULL;
    }

    for (int i = 0; i < num_nodes; i++) {
        key[i] = INF;
        in_mst[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;

    MSTEdge* mst_result = (MSTEdge*)malloc((num_nodes-1) * sizeof(MSTEdge));
     if (!mst_result && num_nodes > 1) {
         free(key); free(parent); free(in_mst);
         fprintf(stderr, "Memory allocation failed for MST result array.\n");
        *mst_edge_count = 0;
        return NULL;
    }
    *mst_edge_count = 0;

    for (int count = 0; count < num_nodes; count++) {
        int u = -1;
        int min_key = INF;

        for (int v_idx = 0; v_idx < num_nodes; v_idx++) {
            if (!in_mst[v_idx] && key[v_idx] < min_key) {
                min_key = key[v_idx];
                u = v_idx;
            }
        }

        if (u == -1) break; 

        in_mst[u] = true;

        if (parent[u] != -1) {
            mst_result[*mst_edge_count].u = parent[u];
            mst_result[*mst_edge_count].v = u;
            mst_result[*mst_edge_count].weight = key[u]; // key[u] stores the edge weight
            (*mst_edge_count)++;
        }

        AdjListNode* node = graph->adj_list_array[u];
        while (node) {
            int v = node->dest;
            int weight = node->weight;
            if (!in_mst[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
            node = node->next;
        }
    }
    
    free(key);
    free(parent);
    free(in_mst);

    if (num_nodes > 0 && *mst_edge_count == 0 && num_nodes > 1) {
        free(mst_result);
        return NULL;
    }
     if (num_nodes == 0 || (num_nodes == 1 && *mst_edge_count == 0)) {
        free(mst_result);
        return NULL;
    }

    return mst_result;
}