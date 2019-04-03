
# %load plotter.py
import numpy as np
import matplotlib.pyplot as plt
import os
import shutil

shutil.rmtree('grahamscan')
os.mkdir('grahamscan')
input_file = input().strip()
inp_points = np.loadtxt(fname = input_file,skiprows = 1)
out_points = np.loadtxt(fname="out.txt")
plt.figure()
x_in = []
y_in = []
for point in inp_points:
	x_in.append(point[0])
	y_in.append(point[1])

plt.scatter(x_in,y_in,edgecolors="blue")
plt.savefig("grahamscan/1.png")
x_out = []
y_out = []
i = 2
for point in out_points:
	x_out.append(point[0])
	y_out.append(point[1])
	plt.figure()
	plt.scatter(x_in,y_in,edgecolors="blue")
	plt.scatter(x_out,y_out,edgecolors="red")
	plt.plot(x_out,y_out,color = 'orange')
	plt.savefig("grahamscan/" + str(i) + ".png")
	i += 1
	
x_out.append(x_out[0])
y_out.append(y_out[0])
plt.plot(x_out,y_out,color='orange')
plt.savefig("grahamscan/" + str(i) + ".png")


# In[21]:


filenames = []
for file in os.listdir("grahamscan"):
    if file.endswith(".png"):
        filenames.append("grahamscan/" + file)
filenames.sort()


# In[24]:


import imageio
images = []
for filename in filenames:
    images.append(imageio.imread(filename))
imageio.mimsave('graham.gif', images,fps = 3,loop = 1)

