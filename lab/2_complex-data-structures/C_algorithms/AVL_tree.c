#include <stdio.h>
#include <stdlib.h>

struct avl_node {
    int info;
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static int height(struct avl_node *node) {
    return node ? node->height : 0;
}

static int get_balance(struct avl_node *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

static struct avl_node* right_rotate(struct avl_node *y) {
    struct avl_node *x = y->left;
    struct avl_node *T2 = x->right;

    // Rotate
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static struct avl_node* left_rotate(struct avl_node *x) {
    struct avl_node *y = x->right;
    struct avl_node *T2 = y->left;

    // Rotate
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct avl_node* avl_insert(struct avl_node *node, int value) {
    if (node == NULL) {
        struct avl_node *new_node = (struct avl_node *)malloc(sizeof(struct avl_node));
        if (!new_node) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        new_node->info = value;
        new_node->left = new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }

    if (value < node->info)
        node->left = avl_insert(node->left, value);
    else if (value > node->info)
        node->right = avl_insert(node->right, value);
    else
        return node; // No duplicates

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance the node
    int balance = get_balance(node);

    // 4 Cases:

    // Left Left Case
    if (balance > 1 && value < node->left->info)
        return right_rotate(node);

    // Right Right Case
    if (balance < -1 && value > node->right->info)
        return left_rotate(node);

    // Left Right Case
    if (balance > 1 && value > node->left->info) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->info) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

int avl_find(struct avl_node *node, int value) {
    while (node != NULL) {
        if (value == node->info) {
            return 1;
        }
        else if (value < node->info) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return 0;
}

void avl_inorder_print(struct avl_node *node) {
    if (node == NULL) return;
    avl_inorder_print(node->left);
    printf("%d ", node->info);
    avl_inorder_print(node->right);
}

void avl_free(struct avl_node *node) {
    if (node == NULL) return;
    avl_free(node->left);
    avl_free(node->right);
    free(node);
}

