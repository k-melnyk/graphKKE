import numpy as np
from sklearn.metrics.pairwise import euclidean_distances

from .utils import normalize_gram_matrix
import graphkke.graph.graph as gr


class Kernel(object):
    def __init__(self, par):
        self.par = par
        super(Kernel, self).__init__()

    def compute_gram_matrices(self, graphs, tau=1):
        if not any(isinstance(graph, gr.Graph) for graph in graphs):
            raise TypeError('The list of Graph should be passed')

        gram_xx, gram_xy = self._compute_gram(graphs, tau)

        return gram_xx, gram_xy

    def _compute_gram(self, graphs, tau=1):
        pass


class GaussianKernel(Kernel):
    def __init__(self, sigma):
        self.m_sigma = sigma
        super(GaussianKernel, self).__init__(sigma)

    def _compute_gram(self, graphs, tau=1):
        x, y = self._transform_data(graphs, tau)

        gram_xx = self.__compute_gaussian(x, x)
        gram_xy = self.__compute_gaussian(x, y)

        return gram_xx, gram_xy

    def __compute_gaussian(self, x, y):
        return np.exp(-np.power(euclidean_distances(x, y), 2) / (2 * np.power(self.m_sigma, 2)))

    @staticmethod
    def _transform_data(graphs, tau=1):
        print('Transforming graphs...')

        all_adj_matrix = np.array([graph.get_adj_matrix() for graph in graphs])

        all_adj_matrix = all_adj_matrix.reshape(len(all_adj_matrix), -1)
        x = all_adj_matrix[:-tau]
        y = all_adj_matrix[tau:]

        return x, y


class WlKernel(Kernel):
    def __init__(self, number_of_iterations=1):
        self.n_iterations = number_of_iterations
        super(WlKernel, self).__init__(number_of_iterations)

    def _compute_gram(self, graphs, tau=1):
        n_graphs = len(graphs)

        print('Computing {kernel} kernel...'.format(kernel=self.__class__.__name__))

        gram = gr.wl_subtree_kernel(graphs, self.n_iterations)
        k_normalized = normalize_gram_matrix(gram)
        gram_xx = k_normalized[:n_graphs - tau, :n_graphs - tau]
        gram_xy = k_normalized[:n_graphs - tau, tau:n_graphs]

        return gram_xx, gram_xy
