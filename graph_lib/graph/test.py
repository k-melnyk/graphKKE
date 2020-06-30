import graph_lib as gl

g = gl.Graph([[0,1], [1, 2]], 3)
print(g.get_adj_matrix())
print(g.get_list_of_edges())
