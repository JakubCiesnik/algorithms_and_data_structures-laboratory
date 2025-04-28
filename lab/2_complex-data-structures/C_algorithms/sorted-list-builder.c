#include <stdio.h>
#include <stdlib.h>

struct lista {
    int info;
    struct lista *next;
};

int main() {
    struct lista *list = NULL; // initialise 
    int a = 5;  // Example value to insert
    
    // Insert a into the list
    struct lista *tmp, *tmp2;

    if (list == NULL) { // if list doesn't exist
        list = (struct lista *)malloc(sizeof(struct lista)); // allocate memory for one instance of sruct lista, typecast from void * (generic returned from malloc) to struct lista *
        list->info = a; // go to list, move by offset of info (eg 2 for int), set it to a
        list->next = NULL; 
    } 
    else {
        if (a < list->info) { // if a is smaller than the minimal (first) element of list, insert it at index 0
            tmp = (struct lista *)malloc(sizeof(struct lista));
            tmp->info = a;
            tmp->next = list;
            list = tmp;
        } 
        else { // otherwise insert it at its correct place
            tmp = list;
            while (tmp->next != NULL && tmp->next->info < a) {
                tmp = tmp->next;
            }
            tmp2 = (struct lista *)malloc(sizeof(struct lista));
            tmp2->info = a;
            tmp2->next = tmp->next;
            tmp->next = tmp2;
        }
    }

    // Print the list to verify
    tmp = list;
    while (tmp != NULL) {
        printf("%d -> ", tmp->info);
        tmp = tmp->next;
    }
    printf("NULL\n");

    return 0;
}
