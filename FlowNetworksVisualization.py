import sys
import linecache
import math
import numpy as np
import matplotlib.pyplot as plt


if not linecache.getline(sys.argv[1], 2):
    print("Graphs is empty.")
    sys.exit()

matrix = np.loadtxt(sys.argv[1], dtype = int, skiprows = 1)
weights = np.loadtxt(sys.argv[2], dtype = int)
layers = np.loadtxt(sys.argv[3], dtype = int)

vertices = matrix.shape[0]
x = []
y = []
side = len(layers)

#setting coordinates
from_left = -side
for layer in layers:
    from_left += 2*side/(len(layers)+1)
    from_top = side/2
    for i in range(layer):
        from_top -= side/(layer+1)
        x.append(from_left)
        y.append(from_top)

#setting figure size, drawing and adding labels to verticles
plt.figure(figsize = (10, 10), dpi = 100)
plt.scatter(x, y, c = 'r')
for i in range(vertices):
    xy = (1.1 * x[i], 1.1 * y[i])
    plt.annotate(i + 1, xy)

rows = matrix.shape[0]
columns = matrix.shape[1]

#drawing edges and arrows
for j in range(columns):
    edge_x = []
    edge_y = []
    for i in range(rows):
        if matrix[i][j] != 0:
            edge_x.append(x[i])
            edge_y.append(y[i])
    for i in range(rows):
        if matrix[i][j] == 1:
            edge_x[0] , edge_x[1] = edge_x[1] , edge_x[0]
            edge_y[0] , edge_y[1] = edge_y[1] , edge_y[0]
            break
        if matrix[i][j] == -1:
            break
    plt.plot(edge_x, edge_y, c = 'b')
    plt.annotate( weights[j], xy = (edge_x[0] + (edge_x[1] - edge_x[0])/4, edge_y[0] + (edge_y[1] - edge_y[0])/4), color='r')
    plt.annotate('', xytext = (edge_x[0], edge_y[0]), xy = (edge_x[0] + (edge_x[1] - edge_x[0])/2, edge_y[0] + (edge_y[1] - edge_y[0])/2), color='b', arrowprops={'arrowstyle': '-|>'})

plt.tight_layout()
plt.show()
