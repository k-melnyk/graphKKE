import numpy as np
import itertools

import seaborn as sns
import matplotlib as plt


class GraphSimulation(object):
    """
    The simulation of the benchmark data based on SDE.
    
    Parameters
    ----------
    n_graphs: int
        Number of graphs to be generated.
    n_nodes: int
        Number of nodes in the graph.
    graph_states: array, (n_graphs, )
        Graph states based on k-means clustering of SDE trajectory.
    node_coordinates: 2D array, (n_graphs, )
        Positions of nodes in the time-dependent graph.
        If not passed, then they are sampled from uniform distribution.
    node_labels: array, (n_graphs, n_nodes)
        Labels for each node of each snapshot of time-dependent graph.
        If not passed, then for each snapshot the same node labels are used: [1, ..., n_nodes].
    """
    def __init__(self, n_graphs, n_nodes, graph_states, node_coordinates=None, node_labels=None):
        super(GraphSimulation, self).__init__()
        self.n_graphs = n_graphs
        self.n_nodes = n_nodes
        self.graph_states = graph_states

        if node_coordinates is not None:
            self.node_coordinates = node_coordinates
        else:
            self.node_coordinates = self.simulation_uniform_nodes()

        if node_labels is None:
            self.node_labels = np.arange(self.n_nodes)
        else:
            self.node_labels = node_labels

    def simulation_uniform_nodes(self):
        """
        Generate uniform distributed points for node positions.
        """
        points = [(np.random.uniform(-1.2, 1.2), np.random.uniform(-1.2, 1.2)) for _ in np.arange(self.n_nodes)]

        return np.array(points)

    def choose_random_idx(self, num_points_in_each_class=5):
        return [np.random.choice(np.argwhere(self.graph_states == label).flatten(), size=num_points_in_each_class)
                for label in np.unique(self.graph_states)]

    def create_adj_matrix(self, sde_traj, in_state=None, if_plot=False):
        """
        Method for the generation of snapshots of time-dependent graph.

        Parameters
        ----------
        sde_traj: array, (n_graphs, 2)
            Trajectory of SDE.
        in_state:
            Probability to remove edges inside the circle.
        if_plot:
            If plot examples of graph snapshots.

        Returns
        -------
            graphs: array
                Snapshots of time-dependent graph.
            images: array
                Plotted examples of snapshots of time-dependent graph.
            self.node_coordinates: 2D array, (n_nodes, 2)
                (x, y) coordinates of node positions.
        """
        graphs = []
        images = []
        idx_to_plot = self.choose_random_idx()

        for t in range(self.n_graphs):
            edges_to_remove, nodes_to_remove, adj_matrix = self.edges_to_remove_prob(sde_traj, t, in_state)

            curr_matrix = np.array(adj_matrix)
            np.fill_diagonal(curr_matrix[:, :], 0)
            graphs.append(curr_matrix)

            if if_plot:
                if t in np.hstack(idx_to_plot):
                    images.append(self.plot_graph(sde_traj, sde_traj[t], edges_to_remove, nodes_to_remove, t))

        return graphs, images, self.node_coordinates

    def edges_to_remove_prob(self, sde_traj, t, in_state=None):
        pass

    def plot_graph(self, sde_traj, sde_traj_t, edges_to_remove, nodes_in_circle, t):
        """
        Method for animating the double/5 well potential graphs.

        Parameters
        ----------
        sde_traj: array, (n_graphs, 2)
            Trajectory of SDE.
        sde_traj_t: float
            Coordinates of current SDE position point.
        edges_to_remove: array
            Edge indices to be removed
        nodes_in_circle: array
            Indices of nodes that are in the current circle.
        t: int
            Current time point

        Returns
        --------
        image: imageio
        """
        sns.set(rc={'figure.figsize': (20, 8.27)})
        fig, ax = plt.subplots(ncols=2, sharex=True, sharey=True, gridspec_kw={'wspace': 0.02})

        x = self.node_coordinates[:, 0]
        y = self.node_coordinates[:, 1]

        node_df = pd.DataFrame({'x': x, 'y': y, 'node_labels': self.node_labels, 'color_node': [0]*self.n_nodes})
        node_df.loc[node_df.node_labels.isin(nodes_in_circle), 'color_node'] = 1

        x0 = [pair[0] for pair in list(itertools.combinations(x, 2))]
        x1 = [pair[1] for pair in list(itertools.combinations(x, 2))]
        y0 = [pair[0] for pair in list(itertools.combinations(y, 2))]
        y1 = [pair[1] for pair in list(itertools.combinations(y, 2))]

        ax[0].plot((x0, x1), (y0, y1), color='black', lw=0.1, alpha=0.2, zorder=1)
        sns.scatterplot(x='x', y='y', color='gold', s=400, data=node_df, linewidth=2.5, ax=ax[0], zorder=2)

        self.plot_removed_area(sde_traj_t, sde_traj, ax[0])

        x_to_remove = [(x[i[0]], x[i[1]]) for i in edges_to_remove]
        y_to_remove = [(y[i[0]], y[i[1]]) for i in edges_to_remove]

        for i in range(len(x_to_remove)):
            sns.lineplot(x_to_remove[i], y_to_remove[i], color='red', alpha=0.45, ax=ax[0], zorder=1)

        self.plot_trajectory(sde_traj_t, sde_traj, ax[1])

        ax[0].set_xlabel('$x_1$', fontsize=10)
        ax[1].set_xlabel('$x_1$', fontsize=10)
        ax[0].set_ylabel('$x_2$', fontsize=10)

        for a in ax.flat:
            a.label_outer()

        plt.savefig('/home/katerynam/work/data/artificial/prob_50_500_random/{t}.png'.format(t=t),
                    bbox_inches='tight')

        fig.canvas.draw()
        image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
        image = image.reshape(fig.canvas.get_width_height()[::-1] + (3,))

        return image

    def plot_removed_area(self, sde_traj_t, sde_traj, ax):
        pass

    def plot_trajectory(self, sde_traj_t, sde_traj, ax):
        pass


class DoubleWellGraph(GraphSimulation):
    def __init__(self, n_graphs, n_nodes, graph_states,
                 node_coordinates=None, node_labels=None):
        super(DoubleWellGraph, self).__init__(n_graphs, n_nodes, graph_states,
                                              node_coordinates, node_labels)

    def edges_to_remove_prob(self, sde_traj, t, in_state=None):
        mean_traj = np.mean([item for item in sde_traj if item > 0])

        top_line = sde_traj[t] + mean_traj - 0.1
        bottom_line = sde_traj[t] - mean_traj

        nodes_to_remove = [self.node_labels[i] for i in range(self.node_coordinates.shape[0])
                           if bottom_line < self.node_coordinates[i, 1] < top_line]

        edges_to_remove = list(itertools.combinations(nodes_to_remove, 2))

        prob = (np.random.uniform(size=len(edges_to_remove)) > in_state).astype(int)
        edges_to_remove = [edges_to_remove[i] for i in range(len(edges_to_remove)) if prob[i] == 1]

        adj_matrix = np.ones((self.n_nodes, self.n_nodes))

        for ind, labels in enumerate(edges_to_remove):
            adj_matrix[labels[0], labels[1]], adj_matrix[labels[1], labels[0]] = 0, 0

        return edges_to_remove, nodes_to_remove, adj_matrix

    def plot_removed_area(self, sde_traj_t, sde_traj, ax):
        mean_traj = np.mean([item for item in sde_traj if item > 0])
        top_line = sde_traj_t + mean_traj
        bottom_line = sde_traj_t - mean_traj

        ax.axhline(y=top_line)
        ax.axhline(y=bottom_line)

    def plot_trajectory(self, sim_traj_t, sim_traj, ax1):
        y = np.power(sim_traj, 4) / 4 - np.power(sim_traj, 2) / 2

        ax1.plot(y, sim_traj)
        ax1.set_xlim(-0.5, 0.5)


class LemonGraph(GraphSimulation):
    def __init__(self, radius, n_graphs, n_nodes,
                 graph_states, node_coordinates=None, node_labels=None):
        self.radius = radius
        super(LemonGraph, self).__init__(n_graphs, n_nodes, graph_states, node_coordinates, node_labels)

    @staticmethod
    def if_contain_point(center_x, center_y, radius, x, y):
        """
        Checking if node coordinates are in the circle

        Parameters
        -----------
        center_x: float
            x coordinate of the center of the circle.
        center_y: float
            y coordinate of the center of the circle.
        radius: float
            Radius of the circle.
        x: float
            x coordinate of the point to be checked
        y: float
            y coordinate of the point to be checked

        Returns
        -------
        bool
        """

        if np.power((x - center_x), 2) + np.power((y - center_y), 2) <= np.power(radius, 2):
            return 1
        else:
            return 0

    def edges_to_remove_prob(self, sde_traj, t, in_state=None):
        """
        Select egdes to be removed randomly.

        Parameters
        ----------
        sde_traj: 2D array, (n_graphs, 2)
            Trajectory of SDE.
        t: int
            Current time point.
        in_state: float
            Probability to remove edges in the circle.

        Returns
        -------
            edges_to_remove: array
                Edges to be removed.
            contain_nodes: array
                Indices of nodes that are in the current circle.
            adj_matrix: 2D array, (n_graphs, n_graphs)
                Adjacency matrix of the graph at time point t.
        """
        adj_matrix = np.ones((self.n_nodes, self.n_nodes))

        contain_nodes = np.array([self.node_labels[j] for j in range(self.n_nodes)
                                  if self.if_contain_point(sde_traj[t, 0],
                                                           sde_traj[t, 1], self.radius,
                                                           self.node_coordinates[j, 0],
                                                           self.node_coordinates[j, 1])])

        edges_to_remove = list(itertools.combinations(contain_nodes, 2))

        if in_state is None:
            for edge in edges_to_remove:
                adj_matrix[edge[0], edge[1]], adj_matrix[edge[1], edge[0]] = 0, 0

        else:
            out_state = 1 - in_state

            binom_flags = np.random.binomial(1, out_state, size=self.n_nodes)
            pairs_flags_out_state = list(itertools.combinations(binom_flags, 2))

            for ind, edge in enumerate(edges_to_remove):
                adj_matrix[edge[0], edge[1]], adj_matrix[edge[1], edge[0]] = 0, 0

            other_edges = list(itertools.combinations(self.node_labels, 2))

            for ind, edge in enumerate(other_edges):
                flag_node_0 = pairs_flags_out_state[ind][0]
                flag_node_1 = pairs_flags_out_state[ind][1]

                if flag_node_0 * flag_node_1:
                    np.append(contain_nodes, edge[0])
                    np.append(contain_nodes, edge[1])
                    edges_to_remove.append(edge)

                    adj_matrix[edge[0], edge[1]], adj_matrix[edge[1], edge[0]] = 0, 0

        return edges_to_remove, contain_nodes, adj_matrix

    def plot_removed_area(self, sde_traj_t, sde_traj, ax):
        ax.add_artist(plt.Circle((sde_traj_t[0], sde_traj_t[1]), radius=self.radius, fill=False, color='black'))

    def plot_trajectory(self, sde_traj_t, sde_traj, ax):
        df = pd.DataFrame({'x': sde_traj[:, 0], 'y': sde_traj[:, 1], 'color': self.graph_states})

        sns.scatterplot(x='x', y='y', hue='color', s=150, data=df, color='purple')
        plt.scatter(sde_traj_t[0], sde_traj_t[1], color='red', s=50)
        ax.add_artist(plt.Circle((sde_traj_t[0], sde_traj_t[1]), radius=self.radius, fill=False, color='black'))
