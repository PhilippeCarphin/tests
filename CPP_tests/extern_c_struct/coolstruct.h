#ifndef _COOL_STRUCT_H
#define _COOL_STRUCT_H

struct CoolStruct {
    int integer;
    const char *char_star;
};

#ifdef __cplusplus
extern "C" {
#endif

int print_cool_struct(struct CoolStruct *s);

#ifdef __cplusplus
}
#endif

#endif
