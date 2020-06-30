import os
import glob

import numpy as np
import pandas as pd
import scipy as sp
import itertools

import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import seaborn as sns

from sklearn.preprocessing import normalize
from sklearn.cluster import KMeans


def normalize_gram_matrix(gram_matrix):
    """
    Normalization of Gram matrix.

    Parameters
    ----------
    gram_matrix: 2D array, (n_graphs, n_graphs)
        Gram matrix.

    Returns
    -------
    norm_gram_matrix: 2D array, (n_graphs, n_graphs)
        Normalized gram matrix.
    """
    gram_matrix_normalized = np.zeros(gram_matrix.shape)

    for i in np.arange(gram_matrix.shape[0]):
        for j in np.arange(i, gram_matrix.shape[0]):
            gram_matrix_normalized[i, j] = gram_matrix[i, j] / np.sqrt(gram_matrix[i, i] * gram_matrix[j, j])
    norm_gram_matrix = np.triu(gram_matrix_normalized, 1) + gram_matrix_normalized.T
    return norm_gram_matrix


def sort_eigvec(A):
    """
    Sort of eigenvalues and eigenvectors.

    Parameters
    ----------
    A: 2D array, (n_graphs, n_graphs)
        Matrix to be sorted.

    Return
    ------
    sort_d: array
        Sorted eigenvalues.
    sort_v: 2D array
        Sorted eigenvectors.
    """
    d, v = sp.linalg.eig(A)
    ind = d.argsort()[::-1]

    sort_d = d[ind]
    sort_v = v[:, ind]
    return sort_d, sort_v


def save_metrics(d, v, outdir=None):
    """
    Save plots of dominant eigenvalues and of first and second eigenvectors.

    Parameters
    ----------
    d: array
        Array of eigenvalues.
    v: 2D array
        Array of eigenvectors.
    """
    if outdir is None:
        outdir = os.getcwd()
    else:
        if not os.path.exists(outdir):
            os.mkdir(outdir)

    np.savetxt(os.path.join(outdir, 'eigvalues.csv'), d, delimiter=',')
    np.savetxt(os.path.join(outdir, 'eigfunctions.csv'), v, delimiter=',')

    sns.set()
    plt.rcParams['figure.figsize'] = [20, 10]

    fig = plt.figure()

    ax1 = fig.add_subplot(2, 1, 1)
    sns.scatterplot(np.real(d[0:10]), np.imag(d[0:10]), color='red', ax=ax1)
    plt.xlabel('Real part')
    plt.ylabel('Imaginary part')
    plt.title('Spectrum')

    ax2 = fig.add_subplot(2, 1, 2)
    labels = ['First eigenfunction', 'Second eigenfunction']
    for i in range(2):
        v[:, i] = v[:, i] / np.max(abs(v[:, i]))
        sns.lineplot(range(v.shape[0]), v[:, i], label=labels[i], lw=1, ax=ax2)
    plt.legend(loc='upper left')
    plt.title('The first and the second eigenfunctions')

    if outdir is not None:
        fig.savefig(os.path.join(outdir, 'metrics.png'))
    else:
        plt.show()


def show_graph(x, ind, outdir=None, data_points=None, node_colors=None):
    """
    Plot average graph.

    Parameters
    ----------
    x: 2D array, (n_graphs, n_graphs)
        Average adjacency matrix.
    ind: int
        Index of graph state.
    outdir: str
        Dir to save plots.
    """
    sns.set(rc={'figure.figsize': (20, 8.27)})

    if data_points is not None and not isinstance(data_points, dict):
        keys = np.arange(len(data_points))
        values = list(map(tuple, data_points))
        data_points = dict(zip(keys, values))

    g = nx.Graph()
    graph = nx.from_numpy_array(normalize(x))

    if data_points is not None:
        g.add_nodes_from(data_points.keys())
        pos = data_points
    else:
        pos = nx.spring_layout(g)

    for n, p in pos.items():
        g.nodes[n]['p'] = p

    fig1, ax1 = plt.subplots()

    if node_colors is None:
        node_colors = np.sum(x, axis=1)
    mcl1 = nx.draw_networkx_nodes(graph, pos=pos, with_labels=False, node_color=node_colors, cmap=plt.cm.PuOr,
                                  node_size=80, ax=ax1)

    nx.draw_networkx_edges(graph, pos=pos, edge_color='black', alpha=0.2, ax=ax1)

    divider1 = make_axes_locatable(ax1)
    cax1 = divider1.append_axes("right", size="5%", pad=0.05)
    plt.colorbar(mcl1, cax=cax1)
    plt.grid()
    ax1.tick_params(left=True, bottom=True, labelleft=True, labelbottom=True)

    if outdir is not None:
        if not os.path.exists(outdir):
            os.mkdir(outdir)
        plt.savefig(outdir + 'nodes_' + ind)
    else:
        plt.show()


def plot_avg_graph(graphs, eigenfunc, graph_states, outdir=None, data_points=None):
    """
    Plot average graphs for each state.

    Parameters
    ----------
    graphs: array, (n_graphs, n_nodes, n_nodes)
        Snapshots of the time-dependent graph.
    eigenfunc: array
        Eigenfunction of transfer ooperators.
    graph_states: array
        Number of states for k-means clustering, based on number of dominant eigenvalues.
    outdir: srr
        Dir to save plots.
    data_points: 2D array, (n_nodes, 2)
    """
    k_means = KMeans(n_clusters=graph_states).fit(np.real(eigenfunc[:, :graph_states]))

    for idx in range(graph_states):
        ind = np.argwhere(k_means.labels_ == idx)

        graph_idx = graphs[ind, :].squeeze()
        avg_graphs = np.mean(graph_idx, axis=0)

        show_graph(avg_graphs, str(idx), outdir, data_points)


def combine_plots(path_to_img):
    files = glob.glob(path_to_img + '/*.png')
    output = plt.imread(files[0])[:, :, :3]
    for i in range(1, len(files)):
        img = plt.imread(files[i])[:, :, :3]
        output = concat_images(output, img)

    plt.imsave(path_to_img + '/output.png', output)


def concat_images(imga, imgb):
    new_img = np.concatenate((imga, imgb), axis=1)
    return new_img


def create_graphs_from_matrix(df):
    """
    Create graphs from matrix.

    Parameters
    ----------
    df: pandas DataFrame, (n_time_points, n_features)
        DataFrame of features and time points.
    Returns
    -------
    data_dict: dictionary
        Dictionary with keys: time_points/names of samples;
                              values: 2D array, (n_nodes, n_nodes).
    """
    n_nodes, n_graphs = df.shape[-1], df.shape[0]
    data_dict = {}

    for i in range(n_graphs):
        adj_matrix = np.zeros((n_nodes, n_nodes), dtype=int)

        if isinstance(df, pd.DataFrame):
            name = df.iloc[i, :].name
            current_array = df.iloc[i, :]
        else:
            name = i
            current_array = df[i, :]

        non_zero = np.nonzero(current_array)[0]
        pairs = list(itertools.combinations(non_zero, 2))
        for pair in pairs:
            n1 = pair[0]
            n2 = pair[1]

            adj_matrix[n1][n2] = current_array[n1] * current_array[n2]
            adj_matrix[n2][n1] = current_array[n1] * current_array[n2]

        data_dict[name] = adj_matrix

    return data_dict
