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

verticles = matrix.shape[0]
x = []
y = []
radius = 0.5 * verticles

#setting coordinates
for i in range(verticles):
    x.append(radius * math.cos(i * 2.0 * math.pi / verticles))
    y.append(radius * math.sin(i * 2.0 * math.pi / verticles))

#setting figure size, drawing and adding labels to verticles
plt.figure(figsize = (10, 10), dpi = 100)
plt.scatter(x, y, c = 'r')
for i in range(verticles):
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
      
plt.show()
