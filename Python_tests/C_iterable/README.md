# Consuming a generic iterable in C

This test demonstrates how to iterate over a generic python object implementing
the [iterator protocol](https://docs.python.org/3/c-api/iter.html) (AKA an
iterable).

```C
PyObject *iterate(PyObject *self, PyObject *iterable)
{
    PyObject *iterator = PyObject_GetIter(iterable);

    PyObject *item = NULL;
    while((item = PyIter_Next(iterator)) != NULL){
        PySys_FormatStdout("item: %S, \n", item);
        Py_DECREF(item);
    }

    Py_DECREF(iterator);
    if(PyErr_Occurred()){
        return NULL;
    }

    Py_RETURN_NONE;
}
```

## Refcounts

The iterator we are consuming may give us objects that have any number of other
references pointing to it.  In the first example, `item->ob_refcnt == 5` where
one of those references is the `item` pointer that we have and the other 4 are
simply other references pointing to that object.

In the `Phil()` examples, various ways to make the generator yielding `Phil()`
instances affect the refcount of `item` durint the iteration.

The same is true for the string returned by calling `PyObject_Str(ob)`.  For
example a `pathlib.Path` object has an attribute `self._str` and it's
`__str__(self)` method returns that string so that during the iteration the
we have `py_str->ob_refcnt == 2`: one reference is `self._str` and the other
is the one returned by `PyObject_Str()`.

For the `Phil` examples, we have `py_str->ob_refcnt == 1` because that is the
only reference.

In any case, when we get a reference, we do a single `Py_DECREF()` when we get
rid of it.  The other references are not our problem.
