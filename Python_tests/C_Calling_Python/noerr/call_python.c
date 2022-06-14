#include <stdio.h>
#include <Python.h>

/*
 * This test demonstrates how to use Python code from C.
 *
 * This shows how already existing C code can leverage the power of Python
 * by implementing a function in Python and calling it from C using the
 * Python C API.
 *
 * When Python is used, Py_Initialize() must be called and Py_Finalize() at
 * the end.
 *
 * The function PyImport_ImportModule(char *module) is used to import the
 * python module.
 *
 * PyObject_GetAttrString(PyObject *obj, char *attr) is used to get a function
 * from the module object returned by PyImport_ImportModule().
 *
 * To call the function we create python objects for the arguments.  In this
 * case, the arguments are all C-strings so we use
 *
 *      PyObject *PyUnicode_FromString(char *string);
 *
 * We then use args = PyTuple_New(nargs) and PyTuple_SetItem(args, i, obj) to set
 * our python objects as the components of the tuple.
 *
 * Finally, we use the function
 *
 *      PyObject *result = PyObject_CallObject(func, args);
 *
 * We can then use
 *
 *      PyBytes_AsString(PyUnicode_EncodeFSDefault(result));
 *
 * To get back a C-string from the Python string object result.
 */
struct PythonHelper {
    PyObject *pModule; // philmodule
    PyObject *pyf_get_value; // philmodule.get_value
    PyObject *pyf_set_value; // philmodule.set_value
};

struct PythonHelper python_helper;

int cf_set_value(char *key, char *value);
char *cf_get_value(char *key);

int main(void){

    Py_Initialize();

    /*
     * import philmodule
     */
    PyObject *pModule = PyImport_ImportModule("philmodule");
    if(pModule == NULL){
        PyErr_Print();
        goto err;
    }
    python_helper.pModule = pModule;

    /*
     * python_helper.pyf_get_value = philmodule.get_value
     */
    PyObject *pyf_get_value = PyObject_GetAttrString(pModule, "get_value");
    if(pyf_get_value == NULL){
        PyErr_Print();
        goto err;
    }
    python_helper.pyf_get_value = pyf_get_value;

    /*
     * python_helper.pyf_set_value = philmodule.set_value
     */
    PyObject *pyf_set_value = PyObject_GetAttrString(pModule, "set_value");
    if(pyf_set_value == NULL){
        PyErr_Print();
        goto err;
    }
    python_helper.pyf_set_value = pyf_set_value;

    char *key = "ABC";
    cf_set_value(key, "123");
    printf("The value of %s is '%s'\n", key, cf_get_value(key));

err:
    Py_Finalize();

    return 0;
}

int cf_set_value(char *key, char *value)
{
    /*
     * args = (key, value)
     */
    PyObject *args = PyTuple_New(2);
    PyObject *pKey = PyUnicode_FromString(key);
    PyObject *pValue = PyUnicode_FromString(value);

    PyTuple_SetItem(args, 0, pKey);
    PyTuple_SetItem(args, 1, pValue);

    /*
     * result = philmodule.set_value(*args)
     */
    PyObject *result = PyObject_CallObject(python_helper.pyf_set_value, args);
    if(result == NULL){
        PyErr_Print();
    }
    return PyLong_AsLong(result);
}

char *cf_get_value(char *key)
{
    /*
     * args = (key, )
     */
    PyObject *pKey = PyUnicode_FromString(key);
    PyObject *args = PyTuple_New(1);

    PyTuple_SetItem(args, 0, pKey);

    /*
     * result = philmodule.get_value(*args)
     */
    PyObject *result = PyObject_CallObject(python_helper.pyf_get_value, args);
    if(result == NULL){
        PyErr_Print();
        return NULL;
    }
    return PyBytes_AsString(PyUnicode_EncodeFSDefault(result));
}


/*
 * Do we need a global struct?
 *
 * To keep the imported module and functions available for use
 * in the wrappers, I have created a global struct where the
 * PyObject* for the module and its two functions are stored
 * as fields.
 *
 * I think you could do stuff using the static keyword inside function
 * to keep the reference and not import at every call.
 *
 * cf_get_value(char *key){
 *     static PyObject *pFunc = PyObject_GetAttrString(module, "get_value");
 *     ...
 * }
 *
 * But you still need the module, which I guess you could do
 *
 * cf_get_value(char *key){
 *     static PyObject *pMod  = PyImport_ImportModule("philmodule");
 *     static PyObject *pFunc = PyObject_GetAttrString(module, "get_value");
 *     ...
 * }
 *
 * The print('IMPORTING') in the python code allows us to show that calling
 * PyImport_ImportModule("philmodule") multiple times only prints 'IMPORTING'
 * once.  Therefore the static thing with an import in multiple functions
 * would be OK.
 *
 * However it becomes inconvenient to handle importing errors in these wrapper
 * functions so I prefer to import everything with proper error handling at
 * the cost of having to store the python objects in some kind of global struct.
 */
