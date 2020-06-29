from setuptools import setup, Extension
from setuptools.command.build_py import build_py as _build_py


class build_py(_build_py):
    def run(self):
        self.run_command("build_ext")
        return super().run()

GraphLib_c_ext = Extension(name='_GraphLib_c',
                           swig_opts=['-c++'],
                           extra_compile_args=['-O2'],
                           sources=['GraphLib_c.i'])

setup(name='graph_lib',
      version='0.1',
      description='Library for the analysis of graph-structured and tree-structured data',
      url='https://github.com/KaterynaMelnyk/graphKKE.git',
      author='Kateryna Melnyk',
      author_email='kateryna.melnyk96@gmail.com',
      cmdclass={'build_py': build_py},
      ext_modules=[GraphLib_c_ext],
      py_modules=['GraphLib_c'],
      scripts=['graph_lib.py'])
