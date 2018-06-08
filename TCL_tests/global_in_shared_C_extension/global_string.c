// ref http://wiki.tcl.tk/11153
#include <tcl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define C_PRINT(...) (printf("C:%s():%d:", __func__, __LINE__),printf(__VA_ARGS__))
#define GSTR_ERROR -1
#define GSTR_SUCCESS 0

static char global_string[1024];

int Global_string_Init(Tcl_Interp *interp);
static int Global_string_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int dispatch_subcommand(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result);
static int get_index(const char *str, const char **argv);
static int set_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result);
static int show_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result);
static int get_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result);
static int tcl_print_args(int objc, Tcl_Obj *const objv[]);

typedef int GstrCode;
typedef int TclCode;
/*******************************************************************************
 * Mandatory function.  The name is important:
 * For a shared library named lib<name>.so, TCL will expect a function called
 * <Name>_Init(Tcl_Interp *interp).  This function tells TCL which commands the
 * library provides and binds a C function to be called when TCL executes these
 * commands.
 * The command also needs to be non-stati
*******************************************************************************/
TclCode Global_string_Init(Tcl_Interp *interp)
{
    /*
     * A TCL initialisation function
     */
    if(Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL){
        return TCL_ERROR;
    }

    /*
     * Saying what commands the package provides
     */
    if(Tcl_PkgProvide(interp, "global_string", "1.0") == TCL_ERROR){
        return TCL_ERROR;
    }

    /*
     * Saying what the callback is for a command.
     */
    Tcl_CreateObjCommand(interp, "global_string", Global_string_Cmd, NULL, NULL);

    return TCL_OK;
}

/*******************************************************************************
 * Callback for a TCL command.  TCL expects callbacks to have these arguments
 * which are pretty self explanatory.
 * Note that if the return of this command is TCL_ERROR, your TCL code will not
 * receive the result stored in tcl_result
*******************************************************************************/
static TclCode Global_string_Cmd(ClientData cdata, Tcl_Interp *interp,
                              int objc, Tcl_Obj *const objv[])
{
    (void) cdata;
    // tcl_print_args(objc, objv);

    Tcl_Obj *tcl_result = NULL;
    if(dispatch_subcommand(objc-1, objv + 1, &tcl_result) == GSTR_ERROR){
       C_PRINT("dispatch_subcommand retured with GSTR_ERROR\n");
       return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, tcl_result);
    return TCL_OK;
}


/*******************************************************************************
 * Handle the TCL command
*******************************************************************************/
static GstrCode dispatch_subcommand(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result)
{
   static const char *lookup_cmd[] = {
      "set_value",
      "show_value",
      "get_value",
      NULL
   };

   enum cmd { SET_VALUE, SHOW_VALUE, GET_VALUE, NONE };

   if(objc < 1){
      *tcl_result = Tcl_NewStringObj("ERROR : no command supplied", -1);
      C_PRINT("No subcommand provided\n");
      return GSTR_ERROR;
   }

   const char *subcommand = Tcl_GetString(objv[0]);

   switch(get_index(subcommand, lookup_cmd)) {
      case -1:
         *tcl_result = Tcl_NewStringObj("Unknown subcommand", -1);
         C_PRINT("No subcommand provided\n");
         return GSTR_ERROR;
      case SET_VALUE:
         return set_value_cmd(objc-1, objv+1, tcl_result);
      case SHOW_VALUE:
         return show_value_cmd(objc-1, objv+1, tcl_result);
      case GET_VALUE:
         return get_value_cmd(objc-1, objv+1, tcl_result);
      default:
         *tcl_result = Tcl_NewStringObj("ERROR", -1);
         C_PRINT("Impossible case\n");
         return GSTR_ERROR;
   }
}

/*
 * Get the index where str occurs in the table objv
 */
GstrCode get_index(const char *str, const char **str_array)
{
   int retval = -1;
   int i = 0;
   for(const char **s = str_array; *s != NULL; s++, i++){
      if(strcmp(str, *s) == 0){
         retval = i;
         goto out;
      }
   }
out:
   return retval;
}

/*******************************************************************************
 *
*******************************************************************************/
static GstrCode set_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result){
   if(objc < 1){
      global_string[0] = 0;
   } else {
      strcpy(global_string, Tcl_GetString(objv[0]));
   }
   *tcl_result = Tcl_NewStringObj("SET_TO RESULT", -1);
   return GSTR_SUCCESS;
}

/*******************************************************************************
 *
*******************************************************************************/
static GstrCode show_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result){
   (void) objc;
   (void) objv;
   C_PRINT("The global_string has value %s\n", global_string);
   *tcl_result = Tcl_NewStringObj("SHOW_VALUE RESULT", -1);
   return GSTR_SUCCESS;
}

/*******************************************************************************
 *
*******************************************************************************/
static GstrCode get_value_cmd(int objc, Tcl_Obj *const objv[], Tcl_Obj **tcl_result)
{
   (void) objc;
   (void) objv;
   *tcl_result = Tcl_NewStringObj(global_string, -1);
   return GSTR_SUCCESS;
}

/*******************************************************************************
 * Print arguments of TCL command
*******************************************************************************/
static GstrCode tcl_print_args(int objc, Tcl_Obj *const objv[]){
    for(int i=0; i<objc; ++i){
        C_PRINT("Tcl_GesString(objv[%d])=%s\n",i, Tcl_GetString(objv[i]));
    }
    return TCL_OK;
}
