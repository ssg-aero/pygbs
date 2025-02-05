# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'PyGbs'
copyright = '2025, SSG AERO S.A.S.'
author = 'Sébastien Raymond'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinx.ext.autodoc",  # Ajoute cette ligne si elle n'y est pas
    "sphinx.ext.napoleon",  # Pour la prise en charge des docstrings au format NumPy/Google
    "nbsphinx",
]


templates_path = ['_templates']
exclude_patterns = []



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

# html_theme = 'alabaster'
html_theme = 'piccolo_theme'
html_static_path = ['_static']

nbsphinx_execute = 'always'
