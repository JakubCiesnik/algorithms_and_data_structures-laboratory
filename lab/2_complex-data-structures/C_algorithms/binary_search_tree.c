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

void bst_free(struct bst_node *root) {
    if (root == NULL) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

