import numpy as np
import graphkke.graph.GraphLib_c as gl_c


class Graph(object):
    def __init__(self, graphs, num_nodes=None):
        if num_nodes is None:
            self.this = gl_c.Graphii(graphs)
        else:
            self.this = gl_c.Graphii(graphs, num_nodes)

    def __repr__(self):
        return '{}({})'.format(self.__class__.__name__, self.this)

    def get_num_nodes(self):
        return self.this.GetNumberOfNodes()

    def get_list_of_edges(self):
        return self.this.GetVectorOfEdges()

    def add_node_labels(self, node_labels):
        self.this.AddNodeLabels(node_labels)

    def add_list_of_edges(self, adj_list):
        self.this.AddVectorOfEdges(adj_list)

    def get_node_labels(self):
        return self.this.GetAllNodeLabels()

    def get_node_neighbors(self, node_index):
        return self.this.GetNodeNeighbors(node_index)

    def get_adj_matrix(self):
        return self.this.GetAdjMatrix()


def wl_subtree_kernel(graphs, n_iterations):
    kernel = gl_c.WLSubtreeKernelii(graphs, n_iterations)
    return np.array(kernel)
