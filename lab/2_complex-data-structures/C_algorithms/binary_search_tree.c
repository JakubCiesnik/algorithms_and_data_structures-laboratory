// bst_module.c
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
    int info;
    struct bst_node *left;
    struct bst_node *right;
};

struct bst_node* bst_insert(struct bst_node *root, int value) {
    if (root == NULL) {
        struct bst_node *node = (struct bst_node *)malloc(sizeof(struct bst_node));
        if (node == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        node->info = value;
        node->left = node->right = NULL;
        return node;
    }

    if (value < root->info) {
        root->left = bst_insert(root->left, value);
    } else {
        root->right = bst_insert(root->right, value);
    }

    return root;
}

int bst_find(struct bst_node *root, int value) {
    while (root != NULL) {
        if (value == root->info) {
            return 1; // Found
        }
        else if (value < root->info) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return 0; // Not found
}

void bst_inorder_print(struct bst_node *node) {
    if (node == NULL) return;
    bst_inorder_print(node->left);
    printf("%d ", node->info);
    bst_inorder_print(node->right);
}


// Get Height of BST
int bst_get_height(struct bst_node *root) {
    if (root == NULL) return -1; // Height of empty tree is -1
    int left_height = bst_get_height(root->left);
    int right_height = bst_get_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

// Helper: store inorder traversal into array
void bst_inorder_store(struct bst_node *node, int *array, int *index) {
    if (node == NULL) return;
    bst_inorder_store(node->left, array, index);
    array[(*index)++] = node->info;
    bst_inorder_store(node->right, array, index);
}

// Helper: build balanced BST from sorted array
struct bst_node* bst_build_balanced(int *array, int start, int end) {
    if (start > end) return NULL;
    int mid = start + (end - start) / 2;
    struct bst_node *root = (struct bst_node *)malloc(sizeof(struct bst_node));
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    root->info = array[mid];
    root->left = bst_build_balanced(array, start, mid - 1);
    root->right = bst_build_balanced(array, mid + 1, end);
    return root;
}

// Balance the BST

void bst_free(struct bst_node *root) {
    if (root == NULL) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

// Count the number of nodes in the BST
int bst_count_nodes(struct bst_node *node) {
    if (node == NULL) return 0;
    return 1 + bst_count_nodes(node->left) + bst_count_nodes(node->right);
}

// Balance the BST
struct bst_node* bst_balance(struct bst_node *root) {
    if (root == NULL) return NULL;

    // Step 1: Count nodes
    int node_count = bst_count_nodes(root);

    // Step 2: Store inorder traversal
    int *array = (int *)malloc(node_count * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    int index = 0;
    bst_inorder_store(root, array, &index);

    // Step 3: Free old tree
    bst_free(root);

    // Step 4: Build balanced tree
    struct bst_node *balanced_root = bst_build_balanced(array, 0, node_count - 1);

    free(array);
    return balanced_root;
}
