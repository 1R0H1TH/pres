from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

import numpy as np

def foot(n, c1, p):
	a,b,c = n
	d = -c1
	x1,y1,z1=p
	k = (-a * x1 - b * y1 - c * z1 - d) / (a**2 + b**2 + c**2)
	return np.array([a * k + x1, b * k + y1, c * k + z1])

#creating x,y for 3D plotting
len = 10
x1, y1 = np.meshgrid(range(len), range(len))
x2, y2 = np.meshgrid(range(len), range(len))
x3, z3 = np.meshgrid(range(len+10), range(len+10))

#setting up plot
fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')

P = np.array([1,-2,4])
x = np.array([1,2,2])
n1 = np.array([1,-1,2])
c1 = 3
n2 = np.array([2,-2,1])
c2 = -12

n = np.cross(n1,n2)
c = x.T@n
dist = abs((P-x).T@n)/np.linalg.norm(n)
f = foot(n,c,P)

z1 = ((c1-n1[0]*x1-n1[1]*y1)*1.0)/(n1[2])
z2 = ((c2-n2[0]*x2-n2[1]*y2)*1.0)/(n2[2])
y3 = ((c-n[0]*x3-n[2]*z3)*1.0)/(n[1])

ax.plot_surface(x1, y1, z1, color='b',alpha=0.2)
ax.plot_surface(x2, y2, z2, color='g',alpha=0.2)
ax.plot_surface(x3, y3, z3, color='r',alpha=0.6)

plt.plot([P[0]],[P[1]],[P[2]],'o',label="P")
plt.plot([f[0]],[f[1]],[f[2]],'o',color='black')
plt.plot([P[0],f[0]],[P[1],f[1]],[P[2],f[2]],label="Line $L_1$")

plt.legend()
plt.show()
