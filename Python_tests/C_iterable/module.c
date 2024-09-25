#include <Python.h>
PyObject *iterate(PyObject *self, PyObject *iterable)
{
    (void) self;

    /*
     * Get an iterator.  If the thing is not iterable, the function raises
     *      `TypeError: 'TYPE' object is not iterable`
     */
    PyObject *iterator = PyObject_GetIter(iterable);
    if(iterator == NULL){
        return NULL;
    }

    /*
     * Use PyIter_Next in a while loop to iterate over the items.  The
     * function returns NULL when there are no more items.
     * As shown in https://docs.python.org/3/c-api/iter.html#c.PyIter_Next
     */
    PyObject *item = NULL;
    while((item = PyIter_Next(iterator)) != NULL){

        PyObject *py_str = PyObject_Str(item);
        // The reason for learning to consume iterables in C is to feed some C
        // code that will operate on a char **.
        const char *c_str = PyUnicode_AsUTF8(py_str);

        PySys_FormatStdout("refcnt(item)=%d, refcnt(py_str)=%d, c_str: %s\n", item->ob_refcnt, py_str->ob_refcnt, c_str);

        Py_DECREF(py_str);
        Py_DECREF(item);
        putchar('\n');
    }

    /*
     * Decref the iterator also as shown in the above reference on PyIter_Next()
     */
    Py_DECREF(iterator);
    if(PyErr_Occurred()){
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyMethodDef iteration_methods[] = {
    {
        .ml_name = "iterate",
        .ml_doc = "consume an iterable",
        .ml_meth = iterate,
        // Function takes a single argument (METH_O).  Instead of receiving a
        // tuple of arguments, the C function receives a single PyObject* which
        // is that one argument and we don't need the PyArg_ParseTuple.
        .ml_flags = METH_O,
    },
    { NULL, NULL, 0, NULL },
};

static PyModuleDef iteration = {
    .m_methods = iteration_methods,
    .m_name = "iteration",
    .m_doc = "Test consuming iterable in C",
};

PyMODINIT_FUNC PyInit_iteration(void)
{
    PyObject *m = PyModule_Create(&iteration);
    if(m == NULL){
        return NULL;
    }

    return m;
}

