#include <tcl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define C_PRINT(...) (printf("C:%s():%d:", __func__, __LINE__),printf(__VA_ARGS__))
char global_string[1024];

int get_index(const char *str, const char **argv);
static int set_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result);
static int show_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result);
static int get_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result);
int gs_error(const char *message){
   C_PRINT("ERROR : %s\n", message);
   exit(1);
}

// ref http://wiki.tcl.tk/11153
static int tcl_print_args(int objc, Tcl_Obj *const objv[]){
    for(int i=0; i<objc; ++i){
        C_PRINT("Tcl_GesString(objv[%d])=%s\n",i, Tcl_GetString(objv[i]));
    }
    return TCL_OK;
}
static int
dispatch_subcommand(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result)
{
   static const char *lookup_cmd[] = {
      "set_value",
      "show_value",
      "get_value",
      NULL
   };

   enum cmd { SET_VALUE, SHOW_VALUE, GET_VALUE, NONE };

   if(objc < 1){
      gs_error("Need subcommand\n");
   }

   const char *subcommand = Tcl_GetString(objv[0]);

   switch(get_index(subcommand, lookup_cmd)) {
      case -1:
         *tcl_result = Tcl_NewStringObj("Unknown subcommand", -1);
         return -2;
      case SET_VALUE:
         return set_value_cmd(objc-1, objv+1, tcl_result);
      case SHOW_VALUE:
         return show_value_cmd(objc-1, objv+1, tcl_result);
      case GET_VALUE:
         return get_value_cmd(objc-1, objv+1, tcl_result);
      default:
         *tcl_result = Tcl_NewStringObj("ERROR", -1);
         return C_PRINT("Impossible case\n"), -1;
   }

}


static int
set_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result){
   if(objc < 1){
      global_string[0] = 0;
   } else {
      strcpy(global_string, Tcl_GetString(objv[0]));
   }
   *tcl_result = Tcl_NewStringObj("SET_TO RESULT", -1);
   return TCL_OK;
}

static int
show_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result){
   (void) objc;
   (void) objv;
   C_PRINT("The global_string has value %s\n", global_string);
   *tcl_result = Tcl_NewStringObj("SHOW_VALUE RESULT", -1);
   return TCL_OK;
}

static int
get_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result)
{
   (void) objc;
   (void) objv;
   *tcl_result = Tcl_NewStringObj(global_string, -1);
   return TCL_OK;
}

static int
Global_string_Cmd(ClientData cdata, Tcl_Interp *interp,
      int objc, Tcl_Obj *const objv[])
{
    (void) cdata;
    // tcl_print_args(objc, objv);

    Tcl_Obj *tcl_result = NULL;
    dispatch_subcommand(objc-1, objv + 1, &tcl_result);

    Tcl_SetObjResult(interp, tcl_result);
    return TCL_OK;
}

int
Global_string_Init(Tcl_Interp *interp)
{
    if(Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL){
        return TCL_ERROR;
    }

    if(Tcl_PkgProvide(interp, "global_string", "1.0") == TCL_ERROR){
        return TCL_ERROR;
    }

    Tcl_CreateObjCommand(interp, "global_string", Global_string_Cmd, NULL, NULL);

    return TCL_OK;
}

int get_index(const char *str, const char **objv)
{
   int retval = -1;
   int i = 0;
   for(const char **s = objv; *s != NULL; s++, i++){
      if(strcmp(str, *s) == 0){
         retval = i;
         goto out;
      }
   }
out:
   return retval;
}

