import matplotlib.pyplot as plt
import numpy as np

inp_points = np.loadtxt(fname="inp_1000_gen.txt",skiprows=1)
# print(inp_points)
x = []
y = []
for point in inp_points:
    x.append(point[0])
    y.append(point[1])
plt.scatter(x,y,edgecolors="lightblue")

out_points = np.loadtxt(fname="out.txt")
# print(out_points)
x = []
y = []
for point in out_points:
    x.append(point[0])
    y.append(point[1])
plt.scatter(x,y,edgecolors="red")
x.append(x[0])
y.append(y[0])
plt.plot(x,y,color="orange")
plt.show()
