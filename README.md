## A library for the analysis of graph-structured and tree-structured data. 

The library contains the fast implementation of Weisfeiler-Lehman graph kernel [0].

## Repository Structure
* **graphlib**: It consists of the most recent dynamic graph embedding approaches, with each files representing a single embedding method. We also have some

## Install
* For setting of rest of the methods, the package uses setuptools, which is a common way of installing python modules. 
  - To install in your home directory, use:
    ```bash
      export PYTHONPATH="/<...>/site-packages/:$PYTHONPATH"
      python setup.py install --user
     ```
  - To install for all users on Unix/Linux:
    ```bash 
       sudo python setup.py install
    ```
## Usage Example

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


