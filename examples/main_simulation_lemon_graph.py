import os
import argparse
import numpy as np
import scipy

import imageio
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

import graphkke.generate_graphs.graph_generation as graph_generation
import graphkke.generate_graphs.generate_SDE as generate_SDE

parser = argparse.ArgumentParser()

parser.add_argument('--input_dir', type=str,
                    default='/home/katerynam/work/data/artificial/test/')
parser.add_argument('--n_graphs', type=int,
                    default=500)
parser.add_argument('--n_nodes', type=int,
                    default=300)
parser.add_argument('--radius', type=float,
                    default=0.6)
parser.add_argument('--n_wells', type=int,
                    default=3)
parser.add_argument('--out_state', type=int,
                    default=0.1)
parser.add_argument('--if_plot', type=bool,
                    default=True)
parser.add_argument('--seed', type=int,
                    default=7)

args = parser.parse_args()


def randb(n, b):
    return b[0] + (b[1] - b[0]) * scipy.rand(1, n)


def rand(n, bounds, boxes):
    d = boxes.size
    x = np.zeros([d, n])
    for i in range(d):
        x[i, :] = randb(n, bounds[i, :])
    return x


if __name__ == '__main__':
    lm = generate_SDE.LemonSlice2D([0.9, 0.9], args.n_graphs, 2, args.n_wells)

    x = rand(1, np.asarray([[-0.5, 0.5], [-0.5, 0.5]]), np.asarray([10, 10]))
    sde_traj = np.asarray(lm.sim_determ_system(x[:, 0]))

    k_means = KMeans(n_clusters=args.n_wells).fit(sde_traj)
    graph_states = k_means.labels_

    # sde_traj = np.load(args.input_dir + 'traj.npy')
    # graph_states = np.load(args.input_dir + 'graph_states.npy')

    plt.scatter(sde_traj[:, 0], sde_traj[:, 1], c=graph_states)
    plt.show()

    sim_graph = graph_generation.LemonGraph(args.radius, args.n_graphs, args.n_nodes,
                                            graph_states)
    graphs, images, node_points = sim_graph.create_adj_matrix(sde_traj, args.out_state, args.if_plot)

    for i, image in enumerate(images):
        imageio.imwrite(args.input_dir + f'/traj_{i}.png', image)
    imageio.mimsave(args.input_dir + '/anim.gif', images, fps=2)

    np.save(os.path.join(args.input_dir + 'traj.npy'), sde_traj)
    np.save(os.path.join(args.input_dir + 'graphs.npy'), graphs)
    np.save(os.path.join(args.input_dir + 'graph_states.npy'), graph_states)
    np.save(os.path.join(args.input_dir + 'node_points.npy'), node_points)

