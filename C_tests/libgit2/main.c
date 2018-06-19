#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <ftw.h>
#include <unistd.h>
#include <git2.h>
#include <stdlib.h>

int unlink_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftw)
{
   (void) typeflag;
   (void) sb;
   (void) ftw;
   if(remove(fpath)){
      perror(fpath);
      return -1;
   }

   return 0;
}


int main(void)
{
   git_libgit2_init();

   git_repository *repo;
   const char *path = "/home/pcarphin/Documents/GitHub/tests/C_tests/libgit2/.git";
   git_repository_init(&repo, path, 0);

   nftw(path, unlink_callback, 64, FTW_DEPTH | FTW_PHYS);

   return 0;
}
