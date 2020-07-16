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
* In order to run the graphKKE method, you need first convert your adjacency matrices or adjacency lists into graph data type.
    - If you have a node labels vector for each graph ```node_labels```, then run:
    ```
    graphs = []
    adj_matrix[np.where(adj_matrix != 0)] = 1
    for ind, graph in enumerate(adj_matrix):
        graph = gl.Graph(graph)
        graph.add_node_labels(node_labels[ind])

        graphs.append(graph)
    ```
 - If you have adjacency matrix ```adj_matrix``` and do not have the vector of node labels:
    ```
    num_nodes = adj_matrix.shape[-1]
    node_labels = list(range(num_nodes))

    graphs = []
    adj_matrix[np.where(adj_matrix != 0)] = 1
    for graph in tqdm.tqdm(adj_matrix):
        graph = gl.Graph(graph)
        graph.add_node_labels(node_labels)

        graphs.append(graph)
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


