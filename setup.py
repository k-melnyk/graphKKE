from setuptools import setup, Extension

GraphLib_c_ext = Extension('_GraphLib_c',
    sources = ['graphkke/graph/GraphLib_c.i'],
    swig_opts = ['-c++'],
    extra_compile_args = ['-std=c++11', '-O2']
)

setup(name='graphkke',
      version='0.1.1',
      description='Library for the analysis of graph-structured and tree-structured data',
      url='https://github.com/KaterynaMelnyk/graphKKE.git',
      author='Kateryna Melnyk',
      author_email='kateryna.melnyk96@gmail.com',
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
                   'Programming Language :: Python :: 3.7'])
