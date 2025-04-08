import os
import sys

sys.path.insert(0, os.path.abspath('../src'))

# project
project = 'Parrot'
author = 'Florian Burger'
# extensions
extensions = [
  'breathe',
]
# config
breathe_projects = {
  f"{project}": "../build/doxygen/xml"
}
breathe_default_project = f"{project}"
# theme
html_theme = 'sphinx_rtd_theme'