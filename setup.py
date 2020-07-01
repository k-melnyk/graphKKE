from setuptools import setup

setup(name='graphkke',
      version='0.1.1',
      description='Library for the analysis of graph-structured and tree-structured data',
      url='https://github.com/KaterynaMelnyk/graphKKE.git',
      author='Kateryna Melnyk',
      author_email='kateryna.melnyk96@gmail.com',
      packages=['graphkke', 'graphkke.graph', 'graphkke.generate_graphs'],
      install_requires=['numpy',
                        'more-itertools',
                        'seaborn',
                        'matplotlib',
                        'scipy',
                        'sklearn',
                        'pandas'],
      classifiers=['Development Status :: 3 - Alpha',
                   'Programming Language :: Python :: 3.7'])
