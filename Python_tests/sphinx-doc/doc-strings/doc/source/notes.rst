Notes
=====

Generating document for whole modules and packages.
---------------------------------------------------

We can use the directives ``.. automodule:: api``

.. automodule:: api
   :no-index:
   :members:
   :undoc-members:

This is something that can go in its own file.

The executable ``spinx-apidoc`` can generate a bunch of files for each module
in a certain directory.  Each file will have an ``.. automodule::<this-module>``

See https://sphinx-rtd-tutorial.readthedocs.io/en/latest/build-the-docs.html#generating-documentation-from-docstrings

Referring to our code
---------------------

First we need to make our code importable by the Sphinx build process.  Once
that is done, we can refer to our code using some directives.

Configuration
^^^^^^^^^^^^^

To make the python module available, we can add some locations to ``sys.path``
in ``conf.py``:

.. code-block:: python

    import pathlib
    import sys
    module_container = pathlib.Path(__file__).parents[2].joinpath("src")
    sys.path.insert(0, str(module_container))

Referencing objects
^^^^^^^^^^^^^^^^^^^

We can use ``.. autofunction:: api.api_func`` to insert the rendered docstring
from the function ``api.api_func``.  We can also add some text to the directive.

.. autofunction:: api.api_func
   :no-index:

   This is some extra text that is in the rst file.

.. note::

   There are many other ``.. autoXZY::`` directives for the other types of objects
   we might want to refer to.  See https://www.sphinx-doc.org/en/master/usage/extensions/autodoc.html

.. note::

   If the docstring follows the sphinx format, then Sphinx produces a beautiful
   rendering of the information in the docstring.

.. note::

   With ``.. autofunction:: api.api_func``, the type hints are reproduced in the
   function signture.  However we may prevent this by using ``.. autofunction::
   api.api_func(user-supplied-text)`` in which case the user supplied text will
   replace the function signature.
   
   .. autofunction:: api.api_func(asdfasdf)

Autodoc for commands
--------------------

See https://sphinx-argparse.readthedocs.io/en/latest/
