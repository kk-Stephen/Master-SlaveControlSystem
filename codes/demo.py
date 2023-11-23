# Import libraries
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# Define the equation
def f(v_l, v_r,e_p):
    return 0.80 * e_p - 0.74 * v_l + 0.01 * v_r - 0.02 * pow(e_p, 2) + 0.58 * e_p * v_l + 0.16 * e_p * v_r - 0.57 * pow(v_l, 2) - 0.52 * v_l * v_r - 0.12 * pow(v_r, 2)

def z_func(we, wv, vl, vr, ep):
    return we * (pow(f(vl, vr, ep), 2) + pow(ep, 2)) + wv * pow((vl - vr), 2) + pow((vl - 0.5), 2) + pow((vr - 0.5), 2)

# Create a 3D axes object
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Generate the data for v_l and v_r
v_l = np.linspace(-1, 1, 50)
v_r = np.linspace(-1, 1, 50)
v_l, v_r = np.meshgrid(v_l, v_r)

# Calculate the values of z
z = z_func(0.5, 0.5, v_l, v_r, -2.0)

# Plot the surface
surf = ax.plot_surface(v_l, v_r, z, cmap='viridis', linewidth=0, antialiased=False)

# Add a color bar and labels
fig.colorbar(surf, shrink=0.5, aspect=10)
ax.set_xlabel('v_l')
ax.set_ylabel('v_r')
ax.set_zlabel('z')

# Show the plot
plt.show()

