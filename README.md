## GraphKKE: Graph Kernel Koopman Embedding. 


## Repository Structure
* **graphkke/algorithm**: consists of the main function for the grapphKKE method;
* **graphkke/graph**: consists of the class Graph and of C++ implemenatation of WL kernel with multithreading. The Python interface is created from a C++ source code that is wrapped with SWIG (http://www.swig.org);
* **graphkke/generate_graphs**: consists of functions and classes for generating the benchmark graphs with metastable behavior;
* **examples**: consists of experiments with the benchmark data and real-world datasets.
* **data**: contains OTU tables and constructed adjacency matrices.


## Install
* The package uses setuptools, which is a common way of installing python modules. To install: 
  - To install in your home directory, use:
    ```
    $ git clone https://github.com/KaterynaMelnyk/GraphLib.git
    $ cd GraphLib
    
    $ python setup.py build
    $ python setup.py install
    ```
## Examples
* In order to run the graphKKE method, you need first convert your array of adjacency matrices ```adj_matrix``` or adjacency lists ```adj_list``` into graph data type, where ```node_labels``` is a list of node labels for each time-point.
    ```python
    from graphkke.algorithm import m_graphkke
    import graphkke.algorithm.kernels as kernels
    import graphkke.graph.graph as gl
    
    graphs = []
    adj_matrix[np.where(adj_matrix != 0)] = 1
    
    for ind, graph in enumerate(adj_matrix):
        graph = gl.Graph(graph)
        graph.add_node_labels(node_labels[ind])

        graphs.append(graph)
    ```
  Or adjacency lists:
    ```python
    graphs = []
    adj_matrix[np.where(adj_matrix != 0)] = 1
    
    for ind, graph in enumerate(adj_list):
        graph = gl.Graph(graph, num_nodes)
        graph.add_node_labels(node_labels[ind])

        graphs.append(graph)
    ```
* For running graphKKE:
```python
# Hyperparameters of graphKKE
epsilon = 0.5
operator = 'K'
num_iterations = 5
k = kernels.WlKernel(num_iterations)

# Run graphKKE method
m_graphkke.graphkke(graphs, k, tau=1, epsilon=epsilon, outdir=outdir)
```

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


