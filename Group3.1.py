from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

#creating x,y for 3D plotting
len = 10
xx, yy = np.meshgrid(range(len), range(len))
#setting up plot
fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')

#Equation of Plane is : n.T * x = c 

#defining planes
n1 = np.array([3,3,0]).reshape((3,1))
c1 = 9
n2 = np.array([1,-1,2]).reshape((3,1))
c2 = 3
n3 = np.array([2,-2,1]).reshape((3,1))
c3 = -12

num = 1 / np.sqrt(2)
rot = np.array([[num, -num],[num, num]])

A = np.array([1,-2,4])
l = np.array([3,0,4])

#corresponding z for planes
z1 = x1*0#((c1-n1[0]*xx-n1[1]*yy)*1.0)/(n1[2])
off = np.sqrt(2.25)
t = np.transpose(np.array([xx,yy,z1]), (1,2,0))
m = [[num, 0, -num],[0,1,0],[num, 0, num]]
x,y,z = np.transpose(np.dot(t, m), (2,0,1))  
z2 = ((c2-n2[0]*xx-n2[1]*yy)*1.0)/(n2[2])
z3 = ((c3-n3[0]*xx-n3[1]*yy)*1.0)/(n3[2])

#plotting planes
ax.plot_surface(x+off, z+off, y, color='r',alpha=0.5)

#plotting line
plt.plot([A[0],l[0]],[A[1],l[1]],[A[2],l[2]],label="Line $L_1$")
plt.plot([point[0]], [point[1]], [point[2]], 'o')
plt.plot([foot[0]], [foot[1]], [foot[2]], 'o')
ax.text(point[0], point[1], point[2], 'P')

plt.xlabel('$x$');plt.ylabel('$y$')
plt.legend(loc='best');plt.grid()

plt.show()

	
	
