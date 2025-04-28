// #include <stdio.h>
// #include <stdlib.h>
//
// struct list_node {
//     int info;
//     struct list_node *next;
// };
//
// int main() {
//     struct list_node *list = NULL; // initialise 
//     int a = 5;  // Example value to insert
//     
//     // Insert a into the list
//     struct list_node *tmp, *tmp2;
//
//     if (list == NULL) { // if list doesn't exist
//         list = (struct list_node *)malloc(sizeof(struct list_node)); // allocate memory for one instance of sruct list_node, typecast from void * (generic returned from malloc) to struct list_node *
//         list->info = a; // go to list, move by offset of info (eg 2 for int), set it to a
//         list->next = NULL; 
//     } 
//     else {
//         if (a < list->info) { // if a is smaller than the minimal (first) element of list, insert it at index 0
//             tmp = (struct list_node *)malloc(sizeof(struct list_node));
//             tmp->info = a;
//             tmp->next = list;
//             list = tmp;
//         } 
//         else { // otherwise insert it at its correct place
//             tmp = list;
//             while (tmp->next != NULL && tmp->next->info < a) {
//                 tmp = tmp->next;
//             }
//             tmp2 = (struct list_node *)malloc(sizeof(struct list_node));
//             tmp2->info = a;
//             tmp2->next = tmp->next;
//             tmp->next = tmp2;
//         }
//     }
//
//     // Print the list
//     tmp = list;
//     while (tmp != NULL) {
//         printf("%d -> ", tmp->info);
//         tmp = tmp->next;
//     }
//     printf("NULL\n");
//
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

// Define a linked list node
struct list_node {
    int info;
    struct list_node *next;
};

// Optional debug printing
static int debug = 0;

// Create a new node
struct list_node* create_node(int value) {
    struct list_node* node = (struct list_node *)malloc(sizeof(struct list_node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->info = value;
    node->next = NULL;
    if (debug) {
        printf("Created node with value %d\n", value);
    }
    return node;
}

// Insert a value into the list in sorted order
void insert_sorted(struct list_node **list, int value) {
    struct list_node *tmp, *tmp2;
    
    if (*list == NULL) {
        *list = create_node(value);
    } 
    else {
        if ((*list)->info > value) {
            tmp = create_node(value);
            tmp->next = *list;
            *list = tmp;
        } 
        else {
            tmp = *list;
            while (tmp->next != NULL && tmp->next->info < value) {
                tmp = tmp->next;
            }
            tmp2 = create_node(value);
            tmp2->next = tmp->next;
            tmp->next = tmp2;
        }
    }

    if (debug) {
        printf("Inserted value %d into the list\n", value);
    }
}

int find_position(struct list_node *list, int value) {
    int position = 0;
    while (list != NULL) {
        if (list->info == value) {
            return position;
        }
        list = list->next;
        position++;
    }
    return -1; // Value not found
}

// Print the list (for debugging)
void print_list(struct list_node *list) {
    struct list_node *tmp = list;
    while (tmp != NULL) {
        printf("%d -> ", tmp->info);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

// Free the entire list
void free_list(struct list_node *list) {
    struct list_node *tmp;
    while (list != NULL) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    if (debug) {
        printf("Freed the list\n");
    }
}

// Enable or disable debug mode
void set_debug(int mode) {
    debug = mode;
}
