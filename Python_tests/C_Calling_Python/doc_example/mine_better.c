#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*
 * Put everything except Py_Initialize and Py_Finalize in a separate function
 * so that returns don't cause Py_Finalize() to be skipped as it was in previous
 * versions.
 *
 * Also added error handling for creation of pName because error handling was
 * done everywhere except there.
 */

int
demo_python(int argc, char **argv)
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    pName = PyUnicode_DecodeFSDefault(argv[1]);
    if (pName == NULL) {
        PyErr_Print();
        fprintf(stderr, "Could not create string object for module name '%s'\n", argv[1]);
        return 1;
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }

    pFunc = PyObject_GetAttrString(pModule, argv[2]);
    /* pFunc is a new reference */

    if (!(pFunc && PyCallable_Check(pFunc))) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        return 1; // The only return that I needed to add
    }

    pArgs = PyTuple_New(argc - 3);
    for (i = 0; i < argc - 3; ++i) {
        pValue = PyLong_FromLong(atoi(argv[i + 3]));
        if (!pValue) {
            Py_DECREF(pArgs); // I think this will Py_DECREF the items that were already added which is what we want.
            Py_DECREF(pModule); // Note that we Py_DECREF the module here.  I think that should be done for any error that occurs after the module has been imported.  For example if pFunc is not callable.
            fprintf(stderr, "Cannot convert argument\n");
            return 1;
        }
        /* pValue reference stolen here: */
        PyTuple_SetItem(pArgs, i, pValue);
    }

    pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);

    if (pValue == NULL) {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        return 1;
    }

    printf("Result of call: %ld\n", PyLong_AsLong(pValue));
    Py_DECREF(pValue);
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);

    return 0;
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
