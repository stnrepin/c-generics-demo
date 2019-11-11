#ifdef GLIST_ITEM_TYPE
#ifndef EXCLUDE_CURRENT_FILE

#ifndef GENERIC_LIST_C
#define GENERIC_LIST_C

#include <stdlib.h>
#include <stdio.h>

#endif // !GENERIC_LIST_C

GLIST_NEW() {
    GLIST* l = malloc(sizeof(GLIST));
    l->head = NULL;
    l->count = 0;

    return l;
}

GLIST_ADD() {
    GLIST_ITEM *item, *l_last;
    GLIST_ITEM_TYPE new_val;

    new_val = val;

#ifdef GLIST_ITEM_TYPE_IS_PTR
    new_val = GLIST_ITEM_TYPE_COPY_FUNC(val);
#endif

    item = malloc(sizeof(GLIST_ITEM));
    item->val = new_val;
    item->next = NULL;

    if (l->head == NULL) {
        l->head = item;
    }
    else {
        l_last = l->head;    
        while (l_last->next != NULL) {
            l_last = l_last->next;
        }
        l_last->next = item;
    }
    l->count++;
}

GLIST_PRINT() {
    GLIST_ITEM *item;

    if (l->count == 0) {
        printf("[]");
        return;
    }

    printf("[ ");

    item = l->head;
    GLIST_ITEM_TYPE_PRINT_FUNC(item->val);

    item = item->next;
    while (item != NULL) {
        if (item != NULL) {
            printf(" -> ");
        }
        GLIST_ITEM_TYPE_PRINT_FUNC(item->val);
        item = item->next;
    }
    printf(" ]\n");
}

GLIST_FREE() {
    GLIST_ITEM *item, *tmp;
    if (l != NULL) {
        item = l->head;
        while (item != NULL) {
            tmp = item->next;
#ifdef GLIST_ITEM_TYPE_IS_PTR
            free(item->val);
#endif
            free(item);

            item = tmp;
        }
    }
    free(l);
}

#endif // !EXCLUDE_CURRENT_FILE
#endif // GLIST_ITEM_TYPE
