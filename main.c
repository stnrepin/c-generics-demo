#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "generic-list.h"

// Include List for int type.
//

void print_int(int i) {
    printf("%d", i);
}
#define GLIST_ITEM_TYPE_PRINT_FUNC print_int

#define GLIST_ITEM_TYPE int
#include "generic-list.h"
#undef GLIST_ITEM_TYPE
#undef GLIST_ITEM_TYPE_NAME
#undef GLIST_ITEM_TYPE_COPY_FUNC
#undef GLIST_ITEM_TYPE_PRINT_FUNC

// Include List for string (char*) type.
//

// List creates a copy of the each held value.
// So we need to define a way of creating of that copy.
char *create_copy_str(char *orig) {
    char * copy = malloc(strlen(orig) + 1); 
    strcpy(copy, orig);
    return copy;
}
#define GLIST_ITEM_TYPE_COPY_FUNC create_copy_str

void print_str(char *str) {
    printf("%s", str);
}
#define GLIST_ITEM_TYPE_PRINT_FUNC print_str

#define GLIST_ITEM_TYPE char*
#define GLIST_ITEM_TYPE_NAME str
#define GLIST_ITEM_TYPE_IS_PTR
#include "generic-list.h"
#undef GLIST_ITEM_TYPE
#undef GLIST_ITEM_TYPE_NAME
#undef GLIST_ITEM_TYPE_IS_PTR
#undef GLIST_ITEM_TYPE_COPY_FUNC
#undef GLIST_ITEM_TYPE_PRINT_FUNC

int main() {
    GList_int *l_int = GList_new_int();
    GList_add_int(l_int, 1);
    GList_add_int(l_int, 2);
    GList_add_int(l_int, 3);

    GList_str *l_str = GList_new_str();
    GList_add_str(l_str, "a");
    GList_add_str(l_str, "b");
    GList_add_str(l_str, "c");

    // But the folowing lines give syntax errors:
    //      GList_add_str(l_int, "123");
    //      GList_add_int(l_int, "123");

    GList_print_int(l_int);
    GList_print_str(l_str);

    GList_free_int(l_int);
    GList_free_str(l_str);
    return 0;
}
