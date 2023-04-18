#include<stdio.h>

#define DEBUG_MESSAGE(fmt, ...) { char t[4096] ; snprintf(t, sizeof(t), fmt, __VA_ARGS__) ; diag_print(t) ; }

#define DBG_PRINT_1(...) \
    do{ \
        fprintf(stderr ,"%s:%d: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fputc('\n', stderr); \
    }while(0)

#define DBG_PRINT_2(...) \
    do{ \
        char t[4096]; \
        int n = snprintf(t, sizeof(t) ,"%s:%d: ", __FILE__, __LINE__); \
        snprintf(t+n, sizeof(t)-n, __VA_ARGS__) ;\
        fprintf(stderr, "%s\n", t); \
    } while(0)

#define DBG_PRINT_3(fmt, ...) \
    do{ \
        fprintf(stderr, "%s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__);\
    } while(0)

void diag_print(char *what){
  fprintf(stderr, "%s\n", what) ;
}
int main(int argc, char **argv){
  // DEBUG_MESSAGE("Ya un probleme"); Expand snprintf(t, sizeof(t), "ya un probleme", ) et la virgule de trop gosse
  DEBUG_MESSAGE("%d", 12 ) ;
  DEBUG_MESSAGE("%d %d", 17 , 18 ) ;
  DEBUG_MESSAGE("%d %d %d", 1, 2, 3) ;
  DBG_PRINT_1("Y'a un probleme");
  DBG_PRINT_2("Y'a un probleme");
  DBG_PRINT_3("Y'a un probleme %d", 0);
  // if(1)
  //     DEBUG_MESSAGE("y'a un probleme :%d", 8);
  // else
  //     DEBUG_MESSAGE("Y'a pas de probleme: %d, 0);

}
