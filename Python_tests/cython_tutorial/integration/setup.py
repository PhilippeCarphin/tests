from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext


source_file = "integration_slow.pyx"

ext_modules = [
        Extension("integration_slow", ["integration_slow.pyx"]),
        Extension("integration_types", ["integration_types.pyx"]),
        Extension("integration_cdef", ["integration_cdef.pyx"]),
        Extension("integration_csin", ["integration_csin.pyx"]),
]

setup(
    name = 'Integrate sine function',
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
)
