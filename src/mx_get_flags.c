#include "uls.h"

static void err_flag(t_flags *fl, char flag) {
    free(fl);
    fl = NULL;
    mx_printerr("uls: illegal option -- ");
    write(2, &flag, 1);
    mx_printerr("\n");
    mx_printerr("usage: uls [-ACGRSTcglmortux1] [file ...]\n");
    exit(-1);
}

static void add_flags(t_flags *flags, char flag) {
    switch(flag) {
        case 'A':
            flags->A = true;
            break;
        case 'G': //Colorized output
            if(isatty(1))
                flags->G = true;
            else
                flags->G = false;
            break;
        case 'R': //Recursive otput of all subfolders
            flags->R = true;
            break;
        case 'S':
            flags->S = true;
            break;
        case 'T': //Complete time information
            flags->T = true;
            break;
        case 'c':
            flags->u = false;
            flags->c = true;
            break;
        case 'u':
            flags->u = true;
            flags->c = false;
            break;
        case 't':
            flags->t = true;
            break;
        case 'r':
            flags->r = 0;
            break;
        case 'g':
            flags->g = true;
            flags->l = true;
            break;
        case 'o':
            flags->o = true;
            flags->l = true;
            break;
        default:
            flags->l = false;
            flags->C = false;
            flags->force = false;
            flags->x = false;
            flags->m = false;

            switch(flag){
                case 'l':
                    flags->l = true;
                    break;
                case 'C':
                    flags->C = true;
                    break;
                case '1':
                    flags->force = true;
                    break;
                case 'x':
                    flags->x = true;
                    break;
                case 'm':
                    flags->m = true;
                    break;
                default:
                    err_flag(flags, flag);
                    break;
            } 
            break;
        
    }
}

t_flags *get_flags(char *argv[], int *count) {
    t_flags *flags = malloc(sizeof(t_flags));
    flags->r = 1; //TODO: Почему не наоборот

    while(argv[(*count)]) {
        if (argv[(*count)][0] == '-') { //Checking if the first argument contains flags
            if (argv[(*count)][1] == '-') { //Exiting when seeing - flag
                (*count)++;
                break;
            }
            if (argv[(*count)][1] == '\0') //Exiting without moving count if the argument is empty
                break;
            for (int j = 1; argv[(*count)][j]; j++) { //Going through all the flags
                add_flags(flags, argv[(*count)][j]); //Checking if it is a flag and then adding it
            }
        }
        else
            break;
        (*count)++;
    }
    return flags;
}
