#include <tcl.h>

// ref http://wiki.tcl.tk/11153
static int print_args(int objc, Tcl_Obj *const objv[]){
    printf("C : %s() BEGIN\n", __func__);
    for(int i=0; i<objc; ++i){
        printf("C : Tcl_GesString(objv[%d])=%s\n",i, Tcl_GetString(objv[i]));
    }
    printf("C : %s() END\n", __func__);
}

static int
Hello_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    printf("C : %s() BEGIN\n", __func__);
    Tcl_SetObjResult(interp, Tcl_NewStringObj("HELLO_CMD RESULT", -1));
    print_args(objc, objv);
    printf("C : %s() END\n", __func__);
    return TCL_OK;
}

int
Hello_Init(Tcl_Interp *interp)
{
    printf("C : %s() BEGIN\n", __func__);
    if(Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL){
        return TCL_ERROR;
    }

    if(Tcl_PkgProvide(interp, "hello", "1.0") == TCL_ERROR){
        return TCL_ERROR;
    }

    Tcl_CreateObjCommand(interp, "hello", Hello_Cmd, NULL, NULL);

    printf("C : %s() END\n", __func__);
    return TCL_OK;
}
