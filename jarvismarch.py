
# coding: utf-8

# In[35]:


import numpy as np
import matplotlib.pyplot as plt
from itertools import islice
import os
import shutil

# In[36]:
shutil.rmtree('jarvismarch')
os.mkdir('jarvismarch')
input_file = input().strip()
inp_points = np.loadtxt(fname = input_file,skiprows = 1)
# out_points = np.loadtxt(fname="out.txt")
x_in = []
y_in = []
for point in inp_points:
    x_in.append(point[0])
    y_in.append(point[1])


# In[41]:


file = open('out.txt','r')
p = int(file.readline())
length = sum(1 for l in file) + 1
a = islice(open('out.txt'),1,length+1)
xp = [x_in[p]]
yp = [y_in[p]]
xq = []
yq = []
i = 0
for u in a:
    if(u[0] == '-'):
        xp.extend(xq)
        yp.extend(yq)
        plt.figure()
        plt.scatter(x_in,y_in,edgecolors = 'blue')
        plt.scatter(xp,yp,edgecolors = 'red')
        plt.plot(xp,yp,color = 'orange')
        plt.savefig('jarvismarch/jm' + str(i) + '.png')
        i += 1
        continue
    else:
        q = int(u)
        xq = [x_in[q]]
        yq = [y_in[q]]
        xtemp = [xp[-1],xq[-1]]
        ytemp = [yp[-1],yq[-1]]
        plt.figure()
        plt.scatter(x_in,y_in,edgecolors = 'blue')
        plt.scatter(xp,yp,edgecolors = 'red')
        plt.scatter(xq,yq,edgecolors = 'green')
        plt.plot(xp,yp,color = 'orange')
        plt.plot(xtemp,ytemp,color = 'blue')
        plt.savefig('jarvismarch/jm' + str(i) + '.png')
        i += 1
        
# plt.show()


# coding: utf-8

# In[1]:


filenames = []
for file in os.listdir("jarvismarch"):
    if file.endswith(".png"):
        filenames.append("jarvismarch/" + file)
filenames.sort()


# In[2]:


import imageio
images = []
for filename in filenames:
    images.append(imageio.imread(filename))
imageio.mimsave('jarvis.gif', images,fps = 3,loop = 1)


