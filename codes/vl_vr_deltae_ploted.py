# Import pandas and matplotlib libraries
import pandas as pd
import matplotlib.pyplot as plt

# Read the csv file into a dataframe
df = pd.read_csv("D:/Github/Master-SlaveControlSystem/codes/data/e_v_data/e_v_data.csv")

# Plot the points in 3D using scatter function
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(df['vl'], df['vr'], df['ep'], c='blue', marker='o')
ax.set_xlabel('vl')
ax.set_ylabel('vr')
ax.set_zlabel('delta_e')

# Show the plot
plt.show()