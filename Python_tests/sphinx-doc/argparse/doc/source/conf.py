# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Repos'
copyright = '2025, Philippe Carphin'
author = 'Philippe Carphin'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration
import sys
import pathlib
p = pathlib.Path(__file__)
root = p.parents[2]
libexec = root.joinpath("libexec", "repos")
print(f"libexec: {libexec}")
sys.path.insert(0, str(libexec))

extensions = [
    'sphinx_rtd_theme',
    'sphinxarg.ext'
]

templates_path = ['_templates']
exclude_patterns = []



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
