#include <gpfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
int print_atime_gpfs(const char *filename){
    struct stat file_info;
    int err = gpfs_stat(filename, (gpfs_stat64_t*)&file_info);
    if(err){
        perror("gpfs_stat");
        return err;
    }

    time_t epoch = file_info.st_atim.tv_sec;

    struct tm *time_info = localtime(&epoch);
    
    char date_string[100];
    strftime(date_string, sizeof(date_string), "%a %Y-%m-%d %H:%M:%S", time_info);
    fprintf(stderr, "  GPFS: atime of file '%s' is '%s'\n", filename, date_string);
    return 0;
}
int print_atime_normal(const char *filename){
    struct stat file_info;
    int err = stat(filename, &file_info);
    if(err){
        perror("gpfs_stat");
        return err;
    }

    time_t epoch = file_info.st_atim.tv_sec;

    struct tm *time_info = localtime(&epoch);

    char date_string[100];
    strftime(date_string, sizeof(date_string), "%a %Y-%m-%d %H:%M:%S", time_info);
    fprintf(stderr, "NORMAL: atime of file '%s' is '%s'\n", filename, date_string);
    return 0;
}
int main(int argc, char **argv)
{
    (void) argc;

    print_atime_gpfs(argv[1]);
    print_atime_normal(argv[1]);
    return 0;
}
