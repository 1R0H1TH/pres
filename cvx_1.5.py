from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')

def plt_pnt(p):
    plt.plot([p[0]], [p[1]], [p[2]], 'o', color='r')
    
def plt_line(a,b):
    plt.plot([a[0],b[0]],[a[1],b[1]],[a[2],b[2]], color='r')
    plt_pnt(a), plt_pnt(b)
def plt_text(p, text):
    ax.text(p[0], p[1], p[2], text)
    
def f(x):
    return np.array([x[0], x[1], x[0]*x[1]])

len = 20
x, y = np.meshgrid(range(len), range(len))
z = x*y


ax.plot_surface(x, y, z, color='b',alpha=0.5)

lamda = 0.4

a = np.array([2,2,4])
b = np.array([17,17,17*17])
p = lamda*a + (1-lamda)*b
m = f(lamda*a + (1-lamda)*b)
plt_line(a,b), plt_line(p,m)
plt_pnt(p), plt_pnt(m)
plt_text(a, 'A'), plt_text(b, 'B')

c,d = np.array([1,17,17]), np.array([17,1,17])
q = lamda*c + (1-lamda)*d
n = f(lamda*c + (1-lamda)*d)
plt_line(c,d), plt_line(q,n)
plt_pnt(q)
plt_pnt(n)
plt_text(c, 'C'), plt_text(d, 'D')
print(n), print(q)

plt.show()
