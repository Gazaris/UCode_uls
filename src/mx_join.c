#include "uls.h"

int mx_max_len_n_g(t_items_arr **names) {
    int max = 0;
    int temp = 0;

    for (int i = 0; names[i]; i++) {
        temp = mx_strlen(names[i]->name);
        if (temp > max)
            max = temp;
    }
    max++;
    return max;
}

void mx_print_spaces_g(int len, int maxlen) {
    int count = 0;

    count = maxlen - len;
    for (int i = 0; i < count; i++)
        mx_printchar(' ');
}

void mx_join(char **res, char *s2) {
    char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
    int i = 0;
    int si = -1;
    char *s1 = *res;

    while(s1[++si]) {
        newstr[i] = s1[si];
        i++;
    }
    si = -1;
    while(s2[++si]) {
        newstr[i] = s2[si];
        i++;
    }
    mx_strdel(&(*res));
    *res = newstr;
}
