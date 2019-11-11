// The code that should be include only once.
//
#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include <stdlib.h>

#define CONCATE_(a, b) a##b
#define CONCATE(a, b) CONCATE_(a, b)

#endif // !GENERIC_LIST_H

// The code that should be included on each instantiation.
//
#ifdef GLIST_ITEM_TYPE

#ifndef GLIST_ITEM_TYPE_NAME
#define GLIST_ITEM_TYPE_NAME GLIST_ITEM_TYPE
#endif // !GLIST_ITEM_TYPE_NAME

// Throw error if some functions aren't defined.
//
#if defined(GLIST_ITEM_TYPE_IS_PTR) && \
    !defined(GLIST_ITEM_TYPE_COPY_FUNC)
#error "A list value should be copyable"
#endif

#ifndef GLIST_ITEM_TYPE_PRINT_FUNC
#error "A list value should be printable"
#endif

// Macros generating structures names.
//
#define MAKE_STRUCT_NAME_(typename, name) \
    name##_##typename
#define MAKE_STRUCT_NAME(typename, name) \
    MAKE_STRUCT_NAME_(typename, name)

// Generate the structures.
//
#define GLIST_ITEM \
    MAKE_STRUCT_NAME(GLIST_ITEM_TYPE_NAME, GListItem)
#define GLIST_ITEM_ CONCATE(GLIST_ITEM, _)

typedef struct GLIST_ITEM_ {
    GLIST_ITEM_TYPE val;
    struct GLIST_ITEM_ *next;
} GLIST_ITEM;

#define GLIST \
    MAKE_STRUCT_NAME(GLIST_ITEM_TYPE_NAME, GList)

typedef struct {
    size_t count;
    GLIST_ITEM *head;
} GLIST;

// Macros generating function declaration: <ret_type> <name>(<params>).
//
#define MAKE_FN_HEAD_(typename, ret_type, action, ...) \
    ret_type GList_##action##_##typename(__VA_ARGS__)
#define MAKE_FN_HEAD(typename, ret_type, action, ...) \
    MAKE_FN_HEAD_(typename, ret_type, action, __VA_ARGS__)

// Macros generating the particular functions.
//
#define GLIST_NEW() \
    MAKE_FN_HEAD(GLIST_ITEM_TYPE_NAME, GLIST*, new, void)

#define GLIST_ADD() \
    MAKE_FN_HEAD(GLIST_ITEM_TYPE_NAME, void, add, GLIST *l, GLIST_ITEM_TYPE val)

#define GLIST_PRINT() \
    MAKE_FN_HEAD(GLIST_ITEM_TYPE_NAME, void, print, GLIST *l)

#define GLIST_FREE() \
    MAKE_FN_HEAD(GLIST_ITEM_TYPE_NAME, void, free, GLIST *l)

// Generate function declarations.
//
GLIST_NEW();
GLIST_ADD();
GLIST_PRINT();
GLIST_FREE();

// GList* GList_new_T(void);
// void GList_print_T(T val);
// void GList_add_T(GList *l, T val);
// void GList_free_T(GList *l);

#include "generic-list.c"

#endif // GLIST_ITEM_TYPE
