#ifdef __APPLE__
#include </usr/include/tcl.h>
#else
#include <tcl.h>
#endif

// ref http://wiki.tcl.tk/11153

static int
Hello_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    Tcl_SetObjResult(interp, Tcl_NewStringObj("Hello, World!", -1));
    puts("A puts from the C code");
    return TCL_OK;
}

int
Hello_Init(Tcl_Interp *interp)
{
    if(Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL){
        return TCL_ERROR;
    }

    if(Tcl_PkgProvide(interp, "hello", "1.0") == TCL_ERROR){
        return TCL_ERROR;
    }

    Tcl_CreateObjCommand(interp, "hello", Hello_Cmd, NULL, NULL);

    return TCL_OK;
}