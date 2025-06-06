# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

# Make my module importable when sphinx is running
import pathlib
import sys
module_container = pathlib.Path(__file__).parents[2].joinpath("src")
sys.path.insert(0, str(module_container))


project = 'docstring-demo'
copyright = '2025, Philippe Carphin'
author = 'Philippe Carphin'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinx_rtd_theme",
    "sphinx.ext.autodoc"
]

templates_path = ['_templates']
exclude_patterns = []
master_doc = 'index'


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
