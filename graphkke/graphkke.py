import os
import numpy as np
import scipy as sp

from .utils import sort_eigvec, save_metrics


def graphkke(graphs, kernel_type, tau=1, epsilon=1e-2, operator='K', outdir=None):
    """
    Main function for graphKKE method.

    Parameters
    ----------
    graphs: array of graph_lib type, (n_graphs)
        Snaphshots of time-dependent graph.
    kernel_type: Kernel type
        Kernel which should be in graphKKE.
    tau: int, default=1
        Lag time.
    epsilon: float, default=1e-2
        Regularization parameter.
    operator: str, default='K'
        'K' (Koopman) or 'P' (Perron-Frobenius) operators to be computed.
    outdir: str, default=None
        Dir to save eigenvalues, eigenvectors and Gram matrix_GG.
    """
    n_graphs = len(graphs) - tau

    gram_xx, gram_xy = kernel_type.compute_gram_matrices(graphs, tau)

    if operator == 'K':
        gram_xy = gram_xy.T

    A = sp.linalg.pinv(gram_xx + epsilon * sp.eye(n_graphs), rcond=1e-15) @ gram_xy

    d, v = sort_eigvec(A)

    if operator == 'K':
        v = gram_xx @ v

    if outdir is not None:
        if not os.path.exists(outdir):
            os.mkdir(outdir)

        np.save(os.path.join(outdir, 'eigenvalues.npy'), d)
        np.save(os.path.join(outdir, 'eigenvectors.npy'), v)
        np.save(os.path.join(outdir, 'gramm.npy'), gram_xx)

        save_metrics(d, v, outdir)
    else:
        return d, v, gram_xx
