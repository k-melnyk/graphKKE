from graph_lib.graphkke import kernels
import graph_lib.graph.graph as gr

print(kernels.WlKernel(2))
g = gr.Graph([[0,1], [1, 2]], 3)
print(g.get_adj_matrix())
print(g.get_list_of_edges())
