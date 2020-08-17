from setuptools import setup, Extension
import numpy

from setuptools.command.build_py import build_py as _build_py

class build_py(_build_py):
    def run(self):
        self.run_command("build_ext")
        return super().run()

GraphLib_c_ext = Extension('_GraphLib_c',
			    sources = ['GraphLib_c.i'],
			    swig_opts = ['-c++'],
			    extra_compile_args = ['-std=c++11', '-O2'],
		            include_dirs=[numpy.get_include()])
			    
setup(name='graphkke',
      version='0.1.1',
      description='Library for the analysis of graph-structured and tree-structured data',
      url='https://github.com/KaterynaMelnyk/graphKKE.git',
      author='Kateryna Melnyk',
      author_email='kateryna.melnyk96@gmail.com',
      cmdclass={'build_py':build_py},
      ext_modules=[GraphLib_c_ext],
      packages=['graphkke', 'graphkke.graph', 'graphkke.generate_graphs', 'graphkke.algorithm'],
      install_requires=['numpy',
                        'more-itertools',
                        'seaborn',
                        'matplotlib',
                        'scipy',
                        'sklearn',
                        'pandas'],
      classifiers=['Development Status :: 3 - Alpha',
                   'Programming Language :: Python :: 3.8'])
