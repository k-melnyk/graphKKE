## A library for the analysis of graph-structured and tree-structured data. 

The library contains the fast implementation of Weisfeiler-Lehman graph kernel [0].

## Repository Structure
* **graphkke/graphkke**: consists of the main function for the grapphKKE method;
* **graphkke/graph**: consists of the class Graph and of C++ implemenatation of WL kernel with multithreading. The Python interface is created from a C++ source code that is wrapped with SWIG (http://www.swig.org);
* **graphkke/generate_graphs**: consists of functions and classes for generating the benchmark graphs with metastable behavior;
* **examples**: consists of experiments with the benchmakr data and real-world dataset.


## Install
* The package uses setuptools, which is a common way of installing python modules. To install: 
  - To install in your home directory, use:
    ```
    $ git clone https://github.com/KaterynaMelnyk/GraphLib.git
    $ cd GraphLib
    
    $ pip install .
    ```
## Examples

## References
   [0]  Shervashidze  N.  et  al.  “Weisfeiler-Lehman  GraphKernels.” In: Journal of Machine Learning Research 12 (2011), pp. 2539–2561.
   ```
    @article{WL,
      title={Weisfeiler-Lehman Graph Kernels.},
      author={Shervashidze N. and Schweitzer P. and Jan van Leeuwen E. and Mehlhorn K. and Borgwardt K.},
      journal={Journal of Machine Learning Research},
      year={2011},
      volume={12},
      pages={2539-2561}
    }
   ```


