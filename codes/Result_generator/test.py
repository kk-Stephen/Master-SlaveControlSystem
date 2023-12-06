import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Sample data
VecStart_x = [0,1,3,5]
VecStart_y = [2,2,5,5]
VecStart_z = [0,1,1,5]
VecEnd_x = [1,2,-1,6]
VecEnd_y = [3,1,-2,7]
VecEnd_z = [1,0,4,9]

# Create a figure object
fig = plt.figure()

# Add a 3D subplot to the figure
ax = fig.add_subplot(111, projection='3d')

# Plot each line in 3D
for i in range(4):
    ax.plot([VecStart_x[i], VecEnd_x[i]], [VecStart_y[i], VecEnd_y[i]], zs=[VecStart_z[i], VecEnd_z[i]])

# Set the labels for the axes
ax.set_xlabel('Distance (cm)')
ax.set_ylabel('Measurement (cm)')
ax.set_zlabel('Angle (degrees)')

# Show the graph
plt.show()