/* https://gist.github.com/starwing/2761647 */
#include <stdio.h>
#include <string.h>

#define COMP_MAX 50

#define ispathsep(ch)   ((ch) == '/' || (ch) == '\\')
#define iseos(ch)       ((ch) == '\0')
#define ispathend(ch)   (ispathsep(ch) || iseos(ch))

char *normpath(char *out, const char *in) {
    char *pos[COMP_MAX], **top = pos, *head = out;
    int isabs = ispathsep(*in);

    if (isabs) *out++ = '/';
    *top++ = out;

    while (!iseos(*in)) {
        while (ispathsep(*in)) ++in;

        if (iseos(*in))
            break;

        if (memcmp(in, ".", 1) == 0 && ispathend(in[1])) {
            ++in;
            continue;
        }

        if (memcmp(in, "..", 2) == 0 && ispathend(in[2])) {
            in += 2;
            if (top != pos + 1)
                out = *--top;
            else if (isabs)
                out = top[-1];
            else {
                strcpy(out, "../");
                out += 3;
            }
            continue;
        }

        if (top - pos >= COMP_MAX)
            return NULL; /* path to complicate */

        *top++ = out;
        while (!ispathend(*in))
            *out++ = *in++;
        if (ispathsep(*in))
            *out++ = '/';
    }

    *out = '\0';
    if (*head == '\0')
        strcpy(head, "./");
    return head;
}

int main(void) {
    char a[][2][260] = {
        { "", "./" },
        { "/..", "/" },
        { "/../", "/" },
        { ".", "./" },
        { "./", "./" },
        { "..", "../" },
        { "../", "../" },
        { "../abc/def", "../abc/def" },
        { "../abc/def/..", "../abc/" },
        { "../abc/././././def/..", "../abc/" },
        { "////../abc/def", "/abc/def" },
        { "/../def", "/def" },
        { "../def", "../def" },
        { "/abc////../def", "/def" },
        { "abc/../def/ghi", "def/ghi" },
        { "/abc/def/../ghi", "/abc/ghi" },
        { "/abc/..abc////../def", "/abc/def" },
        { "/abc/..abc/../def", "/abc/def" },
        { "abc/../def", "def" },
        { "abc/../../def", "../def" },
        { "././", "./" },
        { "abc/..", "./" },
        { "abc/../", "./" },
        { "abc/../..", "../" },
        { "abc/../../", "../" },
        { "a/..", "./" },
        { "a/../", "./" },
        { "a/../..", "../" },
        { "a/../../", "../" },
        { "../../../a", "../../../a" },
        { "../a../../a", "../a" },
        { "cccc/abc////..////.//../", "./" },
        { "aaaa/cccc/abc////..////.//../", "aaaa/" },
        { "..//////.///..////..////.//////abc////.////..////def//abc/..", "../../../def/" },
        { "////////////..//////.///..////..////.//////abc////.////..////def//abc/..", "/def/" },
    };
    int i;
    int pass = 0;
    for (i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
        char buff[260];
        printf("[%d] in> %s\n", i+1, a[i][0]);
        normpath(buff, a[i][0]);
        if (strcmp(buff, a[i][1])) {
            printf("--> %s\n", buff);
            printf("expected: %s\n", a[i][1]);
        }
        else ++pass;
    }
    printf("-----------\nPASS: %d/%d\n", pass, sizeof(a) / sizeof(a[0]));
    return 0;
}
/* cc: flags+='-O2 -Wall -pedantic -ansi' */
