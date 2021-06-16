
//#include <sys/types>
#include <pwd.h>
#include <stdio.h>
//#include <uuid/uuid.h>
//
int print_pwnam(const char *username)
{
    struct passwd *p = getpwnam(username);
    printf("=============== Printing info for \033[1m%s\033[0m ==============\n", username);
    printf("p->pw_name   \033[4m%s\n\033[0m", p->pw_name);
    printf("p->pw_passwd %s\n\033[0m", p->pw_passwd);
    printf("p->pw_uid    \033[4m%u\n\033[0m", p->pw_uid);
    printf("p->pw_gid    %d\n", p->pw_gid);
    printf("p->pw_change %lu\n", p->pw_change);
    printf("p->pw_class  %s\n", p->pw_class);
    printf("p->pw_gecos  %s\n", p->pw_gecos);
    printf("p->pw_dir    \033[4m%s\n\033[0m", p->pw_dir);
    printf("p->pw_shell  \033[4m%s\n\033[0m", p->pw_shell);
    printf("p->pw_expire %ld\n", p->pw_expire);
    printf("p->pw_fields %d\n", p->pw_uid);
    return 0;
}
int main(void)
{
    print_pwnam("pcarphin");
    print_pwnam("pel");
    return 0;
}

