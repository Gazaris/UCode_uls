#include "uls.h"

static t_items_arr *new_node(char *name) {
    t_items_arr *node = malloc(sizeof(t_items_arr));

    node->name = mx_strdup(name);
    node->path = mx_strdup(name);
    node->err = NULL;
    if (stat(name, &(node->info)) == -1)
        node->err = mx_strdup(strerror(errno));	
    node->open = NULL;
    return node;
}

static t_items_arr **create_list(char **name, int count) {
    t_items_arr **new = malloc(sizeof(t_items_arr*) * count);

    int i = 0;
    for (i = 0; name[i]; i++) //Filling an array
        new[i] = new_node(name[i]);
    new[i] = NULL;

    return new;
}

static char **find_names(int argc, char **argv, int first_name_pos, int *count) {
    char **names = NULL;

    if (first_name_pos == argc) { //When no name is specified
        *count = 2;
        names = malloc(sizeof(char*) * 2); //Making a one name array
        names[0] = mx_strdup(".");
        names[1] = NULL;
    }
    else {
        names = malloc(sizeof(char*) * (argc - first_name_pos + 1)); //+1 For NULL
        argc = 0;
        while(argv[first_name_pos]) { //Copying names into the array
            names[argc] = mx_strdup(argv[first_name_pos]);
            first_name_pos++;
            argc++;
        }
        names[argc] = NULL;
        *count = argc + 1;
    }
    return names;
}

t_items_arr **mx_get_names(int argc, char **argv, int first_name_pos) {
    int count = 0; //How many elements in a list (counting NULL in the end)
    char **names = find_names(argc, argv, first_name_pos, &count); //Making a NULL-terminated array of names
    t_items_arr **namesarr = create_list(names, count); //Making a NULL-terminater array

    mx_del_strarr(&names);
    return namesarr;
}
