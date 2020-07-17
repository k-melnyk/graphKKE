## GraphKKE: Graph Kernel Koopman Embedding. 


## Repository Structure
* **graphkke/algorithm**: consists of the main function for the grapphKKE method;
* **graphkke/graph**: consists of the class Graph and of C++ implemenatation of WL kernel with multithreading. The Python interface is created from a C++ source code that is wrapped with SWIG (http://www.swig.org);
* **graphkke/generate_graphs**: consists of functions and classes for generating the benchmark graphs with metastable behavior;
* **examples**: consists of experiments with the benchmark data and real-world datasets, and also a script for generating benchmark data;
* **data**: contains OTU tables and constructed adjacency matrices. Microbiome data is coming from [1] and [2].


## Install
* The package uses setuptools, which is a common way of installing python modules. To install: 
  - To install in your home directory, use:
    ```
    $ git clone https://github.com/KaterynaMelnyk/GraphKKE.git
    $ cd GraphKKE
    
    $ python setup.py build
    $ python setup.py install
    ```
## Examples
* You need first convert your array of adjacency matrices ```adj_matrix``` or adjacency lists ```adj_list``` into graph data type, where ```node_labels``` is a list of node labels for each time-point.
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

* In order to run WL kernel: 
  ```python
  import graphkke.graph.graph as gl
  
  kernel = gl.wl_subtree_kernel(graph, n_iterations)
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
   [1] Hsiao  A.  et  al.  “Members  of  the  human  gut  mi-crobiota involved in recovery from Vibrio choleraeinfection”. In:Nature515 (Jan. 2014), pp. 423–426.
   ```
   @article{CholeraInfOriginal,
    author = {Hsiao A. and Shamsir Ahmed AM. and Subramanian S. and Griffin NW. and Drewry LL. and Petri WA. and Haque R. and Ahmed T. and Gordon JI.},
    year = {2014},
    month = {01},
    title = {Members of the human gut microbiota involved in recovery from Vibrio cholerae infection},
    volume = {515},
    pages={423-426},
    journal = {Nature},
    doi = {10.1038/nature13738}
    }
   ```
   [2]  Caporaso J. et al. “Moving pictures of the humanmicrobiome”.  In:Genome  biology12  (May  2011),R50.
   ```
   @article{MovingPicture,
    author = {Caporaso J. and Lauber C. and Costello E. and Berg-Lyons D. and González A. and Stombaugh J. and Knights D and Gajer P. and Ravel J. and Fierer N. and Gordon J. and Knight R.},
    year = {2011},
    month = {05},
    pages = {R50},
    title = {Moving pictures of the human microbiome},
    volume = {12},
    journal = {Genome biology},
    doi = {10.1186/gb-2011-12-5-r50}
    }
   ```

