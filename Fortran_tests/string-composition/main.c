#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int compose_iris_field_name_string(char **field_names, char* field_types, int nb_fields, char **composed_string)
{
    if(nb_fields <= 0){
        return 1;
    }

    int max_name_len = -1;
    for(int i=0;i<nb_fields;i++){
        int len = strlen(field_names[i]);
        if(len > max_name_len){
            max_name_len = len;
        }
    }

    if((*composed_string = malloc(nb_fields * max_name_len)) == NULL){
        return 1;
    }

    char *p = *composed_string;
    int nadded;
    if((nadded = snprintf(p, 4, "%s", field_names[0])) < 0){
        fprintf(stderr, "ERROR line %d: snprintf\n", __LINE__);
        return 1;
    }
    p+=nadded;

    for(int i = 1; i < nb_fields; i++){
        switch(field_types[i-1]){
            case 'S': case 'V': *p++ = ','; break;
            case 'U':           *p++ = '/'; break;
        }
        if((nadded = snprintf(p, 4, "%s", field_names[i])) < 0){
            fprintf(stderr, "ERROR line %d: snprintf\n", __LINE__);
            return 1;
        }
        p+=nadded;
    }
    *p='\0';
    return 0;
}

int main(int argc, char **argv){
    char *cplatm_cvou_S[] = {"MCP","ALO","ALI","T4O","T4I",
                               "SHO","SHI","LHO","LHI",
                               "TXO","TYO","TXI","TYI",
                               "ZTO","ZQO","ZUO","ZVO",
                               "ZTI","ZQI","ZUI","ZVI",
                               "GLI","I8I","SDI","TMO",
                               "UUO","VVO","I7I","UUI","VVI",
                               "QSO","QSI","ILO","ILI",
                               "ZMO","ZMI","ZHO","ZHI"};
    char cplatm_cvot_S[] = {'S'  ,'S'  ,'S'  ,'S',  'S'  ,
                        'S'  ,'S'  ,'S'  ,'S'  ,
                        'U'  ,'V'  ,'U'  ,'V'  ,
                        'S'  ,'S'  ,'U'  ,'V'  ,
                        'S'  ,'S'  ,'U'  ,'V'  ,
                        'S'  ,'S'  ,'S'  ,'S'  ,
                        'U'  ,'V'  ,'S'  ,'U'  ,'V',
                        'S'  ,'S'  ,'S'  ,'S'  ,
                        'S'  ,'S'  ,'S'  ,'S'};
    char composed_string_stack[sizeof(cplatm_cvou_S)+sizeof(cplatm_cvot_S)];
    char *composed_string;


    int err = compose_iris_field_name_string(cplatm_cvou_S, cplatm_cvot_S, sizeof(cplatm_cvot_S), &composed_string);
    if(err){
        fprintf(stderr, "ERROR: compose_iris_field_name_string\n");
        exit(1);
    }
    fprintf(stderr, "composed_string='%s'\n", composed_string);



    int nadded;
    char *p = composed_string_stack;
    if((nadded = snprintf(p, 4, "%s", cplatm_cvou_S[0])) < 0){
        fprintf(stderr, "ERROR line %d: snprintf\n", __LINE__);
        return 1;
    }
    p+=nadded;
    for(int i = 1; i < sizeof(cplatm_cvot_S); i++){
        switch(cplatm_cvot_S[i-1]){
            case 'S': case 'V': *p++ = ','; break;
            case 'U':           *p++ = '/'; break;
        }
        if((nadded = snprintf(p, 4, "%s", cplatm_cvou_S[i])) < 0){
            fprintf(stderr, "ERROR line %d: snprintf\n", __LINE__);
            return 1;
        }
        p+=nadded;
    }
    *p='\0';
    fprintf(stderr, "composed_string_stack='%s'\n", composed_string_stack);

    if(strcmp(composed_string, composed_string_stack) == 0){
        fprintf(stderr, "\033[32mTHE STRINGS MATCH\033[0m\n");
    } else {
        fprintf(stderr, "\033[31mTHE STRINGS DO NOT MATCH\033[0m\n");
    }

    return 0;
}

