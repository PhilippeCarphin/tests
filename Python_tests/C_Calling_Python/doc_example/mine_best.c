#define PY_SSIZE_T_CLEAN
#include <Python.h>

int
demo_python(int argc, char **argv)
{
    int retval = 1; // error unless we make it to the end with retval = 0;

    PyObject *pModule = PyImport_ImportModule(argv[1]);
    if (pModule == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        goto out;
    }

    PyObject *pFunc = PyObject_GetAttrString(pModule, argv[2]);
    if (!(pFunc && PyCallable_Check(pFunc))) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        goto out_decref_module;
    }

    PyObject *pArgs = PyTuple_New(argc - 3);
    for (int i = 0; i < argc - 3; ++i) {
        PyObject *pValue = PyLong_FromLong(atoi(argv[i + 3]));
        if (!pValue) {
            fprintf(stderr, "Cannot convert argument\n");
            Py_DECREF(pArgs);
            goto out_decref_pfunc;
        }
        PyTuple_SetItem(pArgs, i, pValue);
    }

    PyObject *pResult = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);

    if (pResult == NULL) {
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        goto out_decref_pfunc;
    }

    printf("Result of call: %ld\n", PyLong_AsLong(pResult));
    Py_DECREF(pResult);

    retval = 0;

out_decref_pfunc:
    Py_XDECREF(pFunc);
out_decref_module:
    Py_DECREF(pModule);
out:
    return retval;
}

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }

    Py_Initialize();

    demo_python(argc, argv);

    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
