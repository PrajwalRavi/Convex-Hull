import matplotlib.pyplot as plt
import numpy as np

inp_points = np.loadtxt(fname="ran_inp.txt",skiprows=1)
fig = plt.figure()
ax = fig.add_subplot(111)
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
for xy in zip(x,y):                                       # <--
    ax.annotate('(%s, %s)' % xy, xy=xy, textcoords='data') # <--
plt.scatter(x,y,edgecolors="red")
x.append(x[0])
y.append(y[0])
plt.plot(x,y,color="orange")
plt.show()
