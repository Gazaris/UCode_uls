#pragma once

#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include "libmx.h"
#include "string.h"

#define MX_IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define MX_IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define MX_IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define MX_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define MX_IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define MX_IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define MX_IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define MX_IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)
#define MX_IS_EXEC(mode) ((mode) & S_IXUSR)

#define LS_COLOR_RED   "\x1b[31m"
#define LS_COLOR_RESET "\x1b[0m"

typedef struct s_flags {
    bool A, C, G, R, S, T, c, l, x, t, u, a, force, m, files, g, o;
    int r, ex;
}   t_flags;

typedef struct s_items_arr { //Array for outputed items
    char *name;
    char *path;
    char *err;
    struct stat info;
    struct s_items_arr **open;
}   t_items_arr;

typedef struct s_sz {
    int lnk;
    int sz;
    int group;
    int usr;
    bool is_dev;
}   t_sz;

typedef struct n_type {
    int n_f;
    int n_d;
    int n_e;
    int i;
}   s_type;

//small help functions;
void mx_print_spaces_g(int len, int maxlen);
void mx_del_arr_arr(t_items_arr ***args);
void mx_printstr_g(t_items_arr *args);
void mx_nulloutput(t_flags **fl);
void mx_print_tab(int len, int maxlen);
void mx_err_flag(t_flags **fl, char flag);
void mx_join(char **res, char *s2);
int max_len_names(t_items_arr **names);
int mx_max_len_n_g(t_items_arr **names);

//main program;
t_flags *get_flags(char *argv[], int *count); //Getting flags
t_items_arr **mx_get_names(int argc, char **argv, int i); //Creating an array of items
void mx_opendir(t_items_arr ***names, t_flags *fl);
void mx_out_put_all(t_items_arr ***args, t_flags *fl);
void mx_sort(t_items_arr ***disp, t_flags *fl);
t_items_arr **mx_get_files(t_items_arr ***args, t_flags *fl);
void mx_del_files(t_items_arr ***args, t_flags *fl);
void mx_del_liarr(t_items_arr ***args, t_items_arr **dirs);

//outputs:
void mx_out_put_menu(t_items_arr ***names, t_flags *fl, int flag);
void mx_long_out(t_items_arr **names, t_flags *fl, int flag);
void mx_output_m(t_items_arr **names, t_flags *fl);
void mx_output_g(t_items_arr **names, t_flags *fl);
void mx_output_x(t_items_arr **names);
void mx_output_c(t_items_arr **names);
void mx_out_err(t_items_arr ***error, t_flags *fl);

// flag l
char *mx_get_minor(t_items_arr *print);
char *mx_get_major(t_items_arr *print);
bool mx_check_device(t_items_arr **names, t_sz *size);
char mx_get_file_acl(t_items_arr *print);

// print func
void mx_print_per(t_items_arr *print);
char mx_check_per(t_items_arr *print);
void mx_get_user_name(t_items_arr *print, int usr);
void mx_get_group_name(t_items_arr *print, int group);
void mx_edit_time(t_items_arr *print, char *t, t_flags *fl);
void mx_print_lnk(t_items_arr *print, t_sz *size);
void mx_print_sz(t_items_arr *print, t_sz *size);
void mx_print_symblink(t_items_arr *print);
void mx_print_total(t_items_arr *total, int blk_size);
void mx_print_all(t_items_arr *print, t_sz *size, t_flags *fl);
