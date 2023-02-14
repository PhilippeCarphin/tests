#include <wchar.h>
#include <locale.h>
#include <stdio.h>


int main(void){

    /*
     * NOTE: I only noticed it by trial and error:
     * using printf makes wprintf do nothing and
     * using wprintf makes printf do nothing.  So
     * whichever one is used first is the only one
     * that will do anything and the other one will
     * do nothing forever.
     */
    setlocale(LC_CTYPE, "");
    // char s[] = "😀";
    // printf("this is :D emoji: %s\n", s);

    wchar_t smiley = 0x1F600;
    wprintf(L"sizeof wchar_t: %d\n", sizeof(wchar_t));
    // printf("this is printf\n");
    wprintf(L"Smiley face '%lc'\n", smiley);
    wchar_t ws[] = L"this is a wide string";
    // This demonstrates the use precision to control
    // how much of a string is printed only because
    // I found out you could do that while reading
    //the man page for wprintf.
    wprintf(L"This is a wide string : '%.16ls'\n", ws);

    return 0;
}


