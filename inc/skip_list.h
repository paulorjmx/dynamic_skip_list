#ifndef SKIP_LIST_H
    #define SKIP_LIST_H

        typedef struct t_skip_list SKIP_LIST;

        SKIP_LIST *create();
        void insert(SKIP_LIST **list, int i);
        void delete(SKIP_LIST **list);
#endif
