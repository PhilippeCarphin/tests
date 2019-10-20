
#include <Python.h>



int Cfib(int n)
{
   if(n < 2){
      return n;
   } else {
      return Cfib(n - 1) + Cfib(n - 2);
   }
}

static PyObject* fib(PyObject* self, PyObject *args)
{
   (void) self;
   int n;

   if(!PyArg_ParseTuple(args, "i", &n)){
      return NULL;
   }

   return Py_BuildValue("i", Cfib(n));
}

static PyObject *version(PyObject *self)
{
   (void) self;
   return Py_BuildValue("s", "Version 1.0");
}

static PyMethodDef myMethods[] = {
   {"fib", fib, METH_VARARGS, "Calculates the fibonacci numbers."},
   {"version", (PyCFunction) version, METH_NOARGS, "returns the version."},
   {NULL, NULL, 0, NULL}
};

static struct PyModuleDef myModule = { PyModuleDef_HEAD_INIT, 


};
