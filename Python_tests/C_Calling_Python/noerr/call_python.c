#include <stdio.h>
#include <Python.h>

struct PythonHelper {
    PyObject *pModule;
    PyObject *pyf_get_value;
    PyObject *pyf_set_value;
};

struct PythonHelper python_helper;

int cf_set_value(char *key, char *value);
char *cf_get_value(char *key);

int main(void){

    Py_Initialize();

    PyObject *pModule = PyImport_ImportModule("philmodule");
    if(pModule == NULL){
        PyErr_Print();
        goto err;
    }
    python_helper.pModule = pModule;

    PyObject *pyf_get_value = PyObject_GetAttrString(pModule, "get_value");
    if(pyf_get_value == NULL){
        PyErr_Print();
        goto err;
    }
    python_helper.pyf_get_value = pyf_get_value;

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
    PyObject *args = PyTuple_New(2);
    PyObject *pKey = PyUnicode_FromString(key);
    PyObject *pValue = PyUnicode_FromString(value);

    PyTuple_SetItem(args, 0, pKey);
    PyTuple_SetItem(args, 1, pValue);

    PyObject *result = PyObject_CallObject(python_helper.pyf_set_value, args);
    if(result == NULL){
        PyErr_Print();
    }
    return PyLong_AsLong(result);
}

char *cf_get_value(char *key)
{
    PyObject *pKey = PyUnicode_FromString(key);
    PyObject *args = PyTuple_New(1);

    PyTuple_SetItem(args, 0, pKey);

    PyObject *result = PyObject_CallObject(python_helper.pyf_get_value, args);
    if(result == NULL){
        PyErr_Print();
        return NULL;
    }
    return PyBytes_AsString(PyUnicode_EncodeFSDefault(result));
}


