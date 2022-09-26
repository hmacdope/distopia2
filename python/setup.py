from setuptools import setup, Extension, find_packages
from Cython.Build import cythonize
import numpy as np

libdistopia = Extension(
    name='distopia.libdistopia',
    sources=['distopia/libdistopia.pyx'],
    include_dirs=['../distopia/include/', '../distopia/lib/', np.get_include()],
    library_dirs=['../build'],
    runtime_library_dirs=['../build/'],
    libraries=['distopia'],
    language='c++',
)


setup(
    name='distopia',
    version='0.0.1',
    packages=find_packages(),
    ext_modules=cythonize([libdistopia],
                          compiler_directives={'language_level': 3}, annotate=True),
)
