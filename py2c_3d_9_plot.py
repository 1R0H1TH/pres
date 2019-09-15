from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

x1 = np.genfromtxt("data/meshX1.dat")
y1 = np.genfromtxt("data/meshY1.dat")
z1 = np.genfromtxt("data/meshZ1.dat")

x2 = np.genfromtxt("data/meshX2.dat")
y2 = np.genfromtxt("data/meshY2.dat")
z2 = np.genfromtxt("data/meshZ2.dat")

x3 = np.genfromtxt("data/meshX3.dat")
y3 = np.genfromtxt("data/meshY3.dat")
z3 = np.genfromtxt("data/meshZ3.dat")

P = np.loadtxt("data/P.dat")
foot = np.loadtxt("data/foot.dat")

fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')

ax.plot_surface(x1, y1, z1, color='b',alpha=0.2)
ax.plot_surface(x2, y2, z2, color='g',alpha=0.2)
ax.plot_surface(x3, y3, z3, color='r',alpha=0.6)

plt.plot([P[0]],[P[1]],[P[2]],'o')
plt.plot([foot[0]],[foot[1]],[foot[2]],'o',color='g')
plt.plot([P[0],foot[0]],[P[1],foot[1]],[P[2],foot[2]],label="Line $L_1$")

plt.grid()
plt.axis('equal')
plt.show()
