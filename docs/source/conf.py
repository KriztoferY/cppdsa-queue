import sys
# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'cppdsa-queue'
copyright = '2022 - 2023, KriztoferY (https://github.com/KriztoferY)'
author = 'KriztoferY'
release = '0.1.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

# extensions = []

templates_path = ['_templates']
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'furo'
html_static_path = ['_static']
html_title = 'C++ Queue | cppdsa-queue Library'

# -- Breathe configuration ---------------------------------------------------
# https://breathe.readthedocs.io/en/latest/quickstart.html

# Add the breathe path
sys.path.append(".venv/lib/python3.11/site-packages/breathe/")

# Add breathe as an extension
# extensions = ['sphinx.ext.pngmath', 'sphinx.ext.todo', 'breathe']
extensions = ['breathe']

# Tell breathe about the project(s) with the path to xml generated by doxygen
breathe_projects = {"cppdsa-queue": "../doxygen/xml/"}

# Specify a default project
breathe_default_project = "cppdsa-queue"
