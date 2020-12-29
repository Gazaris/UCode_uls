#include "uls.h"

static int cmp2(t_items_arr *first, t_items_arr *second, t_flags *fl) {
    if (fl->c == 1 && fl->t == 1 && fl->S != 1) {
        if (first->info.st_ctime == second->info.st_ctime) {
            if (first->info.st_ctimespec.tv_nsec == second->info.st_ctimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_ctimespec.tv_nsec < second->info.st_ctimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_ctime < second->info.st_ctime) ? 1 : 0;
    }
    else if (fl->t != 1 && fl->S != 1)
        if (mx_strcmp(first->name, second->name) > 0)
            return 1;
    return 0;
}

static int cmp1(t_items_arr *first, t_items_arr *second, t_flags *fl) {
    if (fl->u == 1 && fl->t == 1 && fl->S != 1) {
        if (first->info.st_atime == second->info.st_atime) {
            if (first->info.st_atimespec.tv_nsec == second->info.st_atimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_atimespec.tv_nsec < second->info.st_atimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_atime < second->info.st_atime) ? 1 : 0;
    }
    else 
        return cmp2(first, second, fl);
}

static int cmp(t_items_arr *first, t_items_arr *second, t_flags *fl) {
    if (fl->S == 1) {
        if (first->info.st_size < second->info.st_size)
            return 1;
        if (first->info.st_size == second->info.st_size)
            return mx_strcmp(first->name, second->name);
    }
    else if (fl->t == 1 && fl->c != 1 && fl->u != 1) {
        if (first->info.st_mtime == second->info.st_mtime) {
            if (first->info.st_mtimespec.tv_nsec == second->info.st_mtimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_mtimespec.tv_nsec < second->info.st_mtimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
    }
    return cmp1(first, second, fl);
}


static int count_sizearr(t_items_arr **disp) {
	int i = 0;

	while(disp[i])
		i++;
	return i;
}

static void swap_li(t_items_arr **bondOne, t_items_arr **bondTwo) {
    t_items_arr *temp = *bondOne;
    *bondOne = *bondTwo;
    *bondTwo = temp;
}

void mx_sort(t_items_arr ***disp, t_flags *fl) {
	t_items_arr **bond = *disp;
	int size = count_sizearr(bond);

	for (int i = 0; i < size; i++) {
		for (int k = i + 1; k < size; k++) {
            if (bond[i]->err != NULL) {
                if (mx_strcmp(bond[i]->name, bond[k]->name) == 1)
                    swap_li(&(bond[i]), &(bond[k]));
            }
            else if (cmp(bond[i], bond[k], fl) == fl->r) {
                swap_li(&(bond[i]), &(bond[k]));
			}
		}
	}
}
