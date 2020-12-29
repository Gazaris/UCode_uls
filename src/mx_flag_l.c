#include "uls.h"

static char *check_grp(t_items_arr *total) {
    struct group *grp = NULL;
    char *name = NULL;
    
    grp = getgrgid(total->info.st_gid);
    if (grp) {
        name = mx_strdup(grp->gr_name);
        return name;
    }
    else {
        name = mx_itoa(total->info.st_gid);
        return name;
    }
}

static char *check_pw(t_items_arr *total) {
    struct passwd *pw = NULL;
    char *name = NULL;

    pw = getpwuid(total->info.st_uid);
    if (pw) {
        name = mx_strdup(pw->pw_name);
        return name;
    }
    else {
        name = mx_itoa(total->info.st_uid);
        return name;    
    }
}

static void count_size(t_sz *size, t_items_arr *total) {
    char *name_grp = check_grp(total);
    char *name_pw = check_pw(total);

    if (size->lnk < total->info.st_nlink)
        size->lnk = total->info.st_nlink;
    if (size->sz < total->info.st_size)
        size->sz = total->info.st_size;
    if (size->group < mx_strlen(name_grp))
        size->group = mx_strlen(name_grp);
    if (size->usr < mx_strlen(name_pw))
        size->usr = mx_strlen(name_pw);
    free(name_grp);
    free(name_pw);
}

static void size_zero(t_sz *size) {
    size->lnk = 0;
    size->sz = 0;
    size->group = 0;
    size->usr = 0;
}

void mx_long_out(t_items_arr **names, t_flags *fl, int flag) {
    t_sz *size = malloc(sizeof(t_sz));
    int blk_size = 0;
    int i = 0;

    size_zero(size);
    for (i = 0; names[i]; i++) {
        blk_size += names[i]->info.st_blocks;
        count_size(size, names[i]);
    }
    if (flag == 1) {
        mx_printstr("total ");
        mx_printint(blk_size);
        mx_printchar('\n');
    }
    mx_check_device(names, size);
    for (i = 0; names[i]; i++)
        mx_print_all(names[i], size, fl);
    free(size);
}
