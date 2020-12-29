#include "uls.h"

int main(int argc, char *argv[]) {
    int count = 1; //Names position
    int exit_code = 0; //Exit code
    t_flags *flags = get_flags(argv, &count); //Getting flags from the first argument
    t_items_arr **args = mx_get_names(argc, argv, count); //Making a NULL-terminater array of item structures

    if(args)
        mx_opendir(&args, flags); //Main part of the program
    if(flags->ex == 1)
        exit_code = 1;
    free(flags);
    flags = NULL;

    return exit_code;
}
