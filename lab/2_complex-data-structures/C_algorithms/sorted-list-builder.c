// Currently have no idea what this does, just copy pasted from pseudo-code.txt

struct lista{
    int info;
    struct list *next;
}
    
list -> NULL;
    
if (list == NULL){
    new(list, a);
    list -> info = a;
    list -> next = null;
}
else{
    if(list->infro >a){
        new(tmp, a);
        tmp -> info = a;
        tmp -> next = list;
        list = tmp;
    }
    else{
        tmp = list;
        while(tmp->next!=null & tmp->next->info < a){
            tmp = tmp -> next;
        }
        new(tmp2, a);
        tmp2->info = a;
        tmp2->next = tmp -> next;
        tmp -> next = tmp2;
        
        
    }
}