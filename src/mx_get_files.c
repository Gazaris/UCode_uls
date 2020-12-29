#include "uls.h"

static t_items_arr *create_file_node(t_items_arr *arg) {
    t_items_arr *node = (t_items_arr *)malloc(1 * sizeof (t_items_arr));

    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    if (arg->err)
        node->err = mx_strdup(arg->err);
    else
        node->err = NULL;
    lstat(node->path, &(node->info));
    if (arg->open != NULL)
        node->open = arg->open;
    else
        node->open = NULL;
    return node;
}

static void create_fde(t_items_arr ***files, t_items_arr ***dirs, 
                        t_items_arr ***errors, t_items_arr ***args) {
    int j = 0;
    int nDir = 0;
    int nErr = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->err == NULL) {
            if (!MX_IS_DIR((*args)[i]->info.st_mode) )
                j++;
            else
                nDir++;
        }
        else
            nErr++;
    if (j > 0)
        *files = malloc((j + 1) * sizeof(t_items_arr *));
    if (nDir > 0)
        *dirs = malloc((nDir + 1) * sizeof(t_items_arr *));
    if (nErr > 0)
        *errors = malloc((nErr + 1) * sizeof(t_items_arr *));
}

static s_type *create_num() {
    s_type *num = malloc(sizeof (s_type));

    num->n_d = 0;
    num->n_e = 0;
    num->n_f = 0;
    num->i = 0;
    return num;
}

static void fdir(t_items_arr **args, s_type *num, t_items_arr ***files, t_items_arr ***dirs) {
    if (!MX_IS_DIR((*args)->info.st_mode)) {
        (*files)[num->n_f++] = create_file_node((*args));
        (*files)[num->n_f] = NULL;
    }
    else {
        (*dirs)[num->n_d++] = create_file_node((*args));
        (*dirs)[num->n_d] = NULL;
    }
}

t_items_arr **mx_get_files(t_items_arr ***args, t_flags *fl) {
    t_items_arr **files = NULL;
    t_items_arr **dirs = NULL;
    t_items_arr **errors = NULL;
    s_type *num = create_num();

    create_fde(&files, &dirs, &errors, args);
    while ((*args)[num->i] != NULL) {
        if ((*args)[num->i]->err == NULL)
            fdir(&(*args)[num->i], num, &files, &dirs);
        else {
            errors[num->n_e++] = create_file_node((*args)[num->i]);
            errors[num->n_e] = NULL;
        }
        num->i++;
    }

    if (num->n_d > 1)
        fl->files = 1;
    mx_del_liarr(args, dirs);
    mx_out_err(&errors, fl);
    free(num);
    return files;
}
