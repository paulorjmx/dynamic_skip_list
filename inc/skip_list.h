#ifndef SKIP_LIST_H
    #define SKIP_LIST_H

        typedef struct t_skip_list SKIP_LIST;
        typedef struct t_node NODE;

        SKIP_LIST *skip_list_create();
        void skip_list_insert(SKIP_LIST **list, int i);
        NODE *skip_list_search(SKIP_LIST *list, int n);
        void skip_list_print_node(NODE *nd);
        void skip_list_remove(SKIP_LIST *list, int n);
        void skip_list_delete(SKIP_LIST **list);
#endif
