from setuptools import setup, Extension

GraphLib_c_ext = Extension('_GraphLib_c',
    sources = ['GraphLib_c.i'],
    swig_opts = ['-c++'],
    extra_compile_args = ['-std=c++11', '-O2']
)

setup(name='GraphLib_c',
       ext_modules=[GraphLib_c_ext])
