#include <dirent.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int print_dirent(const char *base, struct dirent *e){
    printf("==============================\n");
    printf("e->d_ino = %lu\n", e->d_ino);
    printf("e->d_off = %ld\n", e->d_off);
    printf("e->d_reclen = %u\n", e->d_reclen);
    printf("e->d_type = %c\n", e->d_type);
    printf("e->d_name = %s\n", e->d_name);
    int len = strlen(base) + 1 + strlen(e->d_name);
    // char *full_path = malloc(len + 1);
    char full_path[len+1];
    int nbytes = snprintf(full_path, len+1, "%s/%s", base, e->d_name);
    if(nbytes != len){
        printf("Error snprintf\n");
        return 1;
    }

    struct stat st;
    int err = stat(full_path, &st);
    if(err){
        printf("Error stat\n");
        return 1;
    }
    // free(full_path);

    if(S_ISDIR(st.st_mode)){
        printf("DIRECTORY\n");
    } else if(S_ISLNK(st.st_mode)){
        printf("LINK\n");
    } else if(S_ISREG(st.st_mode)){
        printf("REGULAR FILE\n");
    } else {
        printf("or something...\n");
    }

    return 0;
}
int main(int argc, char **argv){

    if(argc < 2){
        printf("Must supply a directory as an argument\n");
        return 1;
    }

    char *base = argv[1];
    DIR *d = opendir(base);
    struct dirent *e;
    int nb_entries = 0;

    while((e = readdir(d)) != NULL){
        nb_entries++;
        int err = print_dirent(base, e);
        if(err){
            printf("Error print_dirent\n");
            return err;
        }
    }

    printf("Number of entries in %s: %d\n", base, nb_entries);

    return 0;
}
