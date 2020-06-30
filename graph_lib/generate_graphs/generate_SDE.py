import copy
import numpy as np


class SDE:
    def __init__(self, c_sigma, n_steps, dim):
        super(SDE, self).__init__()
        self.h = 0.065
        self.n_steps = n_steps
        self.c_sigma = c_sigma
        self.dim = dim

    @staticmethod
    def dW():
        """
        Wiener process.

        Returns
        -------
        rand: float
            Normal distributed value.

        """
        rand = np.random.normal(0.0, 1.0)
        return rand

    def dF(self, x):
        pass

    def F(self, x):
        pass

    def sim_determ_system(self, initial_val):
        """
        Dimulation of a long trajectory.

        Parameters
        ----------
        initial_val: float
            The value of the trajectory at time point 0.

        Returns
        -------
        y: array, (n_steps, 2)
            Simulated trajectory.
        """
        y = np.zeros((self.n_steps, self.dim))

        y[0, :] = copy.copy(initial_val)

        for i in range(1, self.n_steps):
            dF = self.dF(y[i - 1, :])
            for d in range(self.dim):
                y[i, d] = y[i-1, d] + self.h * dF[d] + self.c_sigma[d] * np.sqrt(self.h) * self.dW()
        return y

    def one_traj(self, initial_val):
        """
        Simulation of one trajectory for stochastic dynamical system.

        Parameters
        ----------
        initial_val: float
            The value of the trajectory at time point 0.

        Returns
        -------
        y: array
            One trajectory for the stochastic system.
        """

        y = initial_val
        for _ in range(0, self.n_steps):
            dF = self.dF(y)
            for d in range(self.dim):
                y[d] = y[d] + self.h * dF[d] + self.c_sigma[d] * np.sqrt(self.h) * self.dW()
        return y

    def sim_stoch_system(self, initial_val, dim_traj):
        """
        Simulation of stochastic dynamic system.

        Parameters
        ----------
        initial_val: array
            The value of the trajectory at time point 0.
        dim_traj: int
            The dimension of the system.

        Returns
        -------

        """
        initial_val = initial_val.transpose()
        return [self.one_traj(initial_val[i, :]) for i in range(dim_traj)]


class DoubleWell1D(SDE):
    """
    SDE with double well potential function.
    """
    def __init__(self, c_sigma, n_steps, dim):
        super(DoubleWell1D, self).__init__(c_sigma, n_steps, dim)

    def F(self, x):
        f = np.power(x, 4) / 4 - np.power(x, 2) / 2
        return f

    def dF(self, x):
        """
        Derivative of the potential function.

        Parameters
        ----------
        x: float
            Value at which to compute DF(x).
        Returns
        -------
        dF: float
            dF(x)
        """
        dF = -np.power(x, 3) + x
        return np.array(dF)


class LemonSlice2D(SDE):
    def __init__(self, c_sigma, n_steps, dim, n_wells=5):
        super(LemonSlice2D, self).__init__(c_sigma, n_steps, dim)
        self.n = n_wells

    def F(self, x):
        """
        Computing the potential function.

        Parameters
        ----------
        x: float
            Value at which compute F(x)

        Returns
        -------
            F(x)
        """
        """
        Computing the potential function

        :param x: initial state
        :return:simulated potential
        """
        return np.cos(self.n * np.arctan2(x[1], x[0])) + 10 * np.power((np.sqrt(x[0] ** 2 +
                                                                        x[1] ** 2) - 1), 2)

    def dF(self, initial_val):
        """
        Derivative of the potential function.

        Parameters
        ----------
        x:  array, (x0, x1)
            Value at which compute dF(x0, x1).

        Returns
        -------
            dF(x0, x1).
        """
        # Potential: V = cos(n * atan2(x(2,:), x(1,:))) + 10 * (sqrt(x(1, :). ^ 2 + x(2,:).^ 2) - 1).^ 2

        x = copy.copy(initial_val)
        y_0 = -(self.n * np.sin(self.n * np.arctan2(x[1], x[0])) * x[1] / (x[0] ** 2 + x[1] ** 2) + (
                20 * (np.sqrt(x[0] ** 2 + x[1] ** 2) - 1)) * x[0] / np.sqrt(x[0] ** 2 + x[1] ** 2))

        y_1 = -(-self.n * np.sin(self.n * np.arctan2(x[1], x[0])) * x[0] / (x[0] ** 2 + x[1] ** 2) + (
                20 * (np.sqrt(x[0] ** 2 + x[1] ** 2) - 1)) * x[1] / np.sqrt(x[0] ** 2 + x[1] ** 2))

        return np.asarray([y_0, y_1])
