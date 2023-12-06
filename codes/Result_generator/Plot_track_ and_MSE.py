import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np
from scipy.stats import linregress
import math

led_files = []
foll_files = []

for i in range(5):
    led = os.path.normpath(
        "D:\Github\Master-SlaveControlSystem\data/accuracy/straight0/w/w_w" + "/leader" + str(i) + ".csv")
    foll = os.path.normpath(
        "D:\Github\Master-SlaveControlSystem\data/accuracy/straight0/w/w_w" + "/follower" + str(i) + ".csv")
    led_files.append(led)
    foll_files.append(foll)
avg_file = os.path.normpath(
        "D:\Github\Master-SlaveControlSystem\data/accuracy/straight0/w/w_b/follower_average.csv")
led_dfs = []
foll_dfs = []
led_mse = []
foll_mse = []

for i in range(5):
    led_df = pd.read_csv(led_files[i])
    foll_df = pd.read_csv(foll_files[i])

    led_x = led_df['x'].to_numpy()
    led_y = led_df['y'].to_numpy()
    led_coef = led_df['y'].iat[-1] / led_df['x'].iat[-1]

    led_theta = -math.atan(led_coef)
    R = np.array([[math.cos(led_theta), -math.sin(led_theta)], [math.sin(led_theta), math.cos(led_theta)]])
    points_vector = np.vstack([led_x, led_y])
    rotated_points_vector = np.dot(R, points_vector)
    x_rotated, y_rotated = rotated_points_vector[0], rotated_points_vector[1]
    led_df['x'] = x_rotated
    led_df['y'] = y_rotated

    foll_x = foll_df['x'].to_numpy()
    foll_y = foll_df['y'].to_numpy()
    foll_coef = foll_df['y'].iat[-1] / foll_df['x'].iat[-1]

    foll_theta = -math.atan(foll_coef)
    R = np.array([[math.cos(foll_theta), -math.sin(foll_theta)], [math.sin(foll_theta), math.cos(foll_theta)]])
    points_vector = np.vstack([foll_x, foll_y])
    rotated_points_vector = np.dot(R, points_vector)
    x_rotated, y_rotated = rotated_points_vector[0], rotated_points_vector[1]
    foll_df['x'] = x_rotated
    foll_df['y'] = y_rotated

    # led_df.to_csv(led_files[i])
    # foll_df.to_csv(foll_files[i])
    led_mse.append(np.mean(np.square(led_df['y'])))
    foll_mse.append(np.mean(np.square(foll_df['y'])))

    #print(foll_df.loc[66, 'y'])
    # Append DataFrames to the list for later averaging
    led_dfs.append(led_df)
    foll_dfs.append(foll_df)

    #plt.plot(led_df['x'], led_df['y'], 'o')
    #plt.plot(foll_df['x'], foll_df['y'], 'o', label=str(i))

# Calculate average DataFrames
avg_led_df = pd.concat(led_dfs).groupby(level=0).mean()
avg_foll_df = pd.concat(foll_dfs).groupby(level=0).mean()
# avg_foll_df.to_csv(avg_file)

avg_led_mse = avg_foll_mse = 0

for i in range(len(led_mse)):
    avg_led_mse = avg_led_mse + led_mse[i]
    avg_foll_mse = avg_foll_mse + foll_mse[i]
    print('leader'+str(i) + ': ' + str(round(led_mse[i],2)))
    print('follower'+str(i) + ': ' + str(round(foll_mse[i],2)))

print('average leader mse:' + str(round(avg_led_mse / 5, 2)))
print('average follower mse:' + str(round(avg_foll_mse / 5,2)))

print(led_mse)
print(foll_mse)

# # Plot Leader tracks
# plt.figure(figsize=(10, 5))
# plt.subplot(1, 2, 1)  # 1 row, 2 columns, 1st subplot
# plt.title("Leader tracks")
# for i in range(5):
#     plt.plot(led_dfs[i]['x'], led_dfs[i]['y'], 'o', label=f"Leader {i}")
#
# plt.plot(avg_led_df['x'], avg_led_df['y'], linewidth=5, label='Leader Average')
# plt.grid(True, which='both')
# plt.axhline(y=0, color='k')
# plt.axvline(x=0, color='k')
# plt.xlabel('x')
# plt.ylabel('Vertical offset')
# plt.ylim(-15, 15)
# plt.legend(loc='upper right')
#
# # Plot Follower tracks
# plt.subplot(1, 2, 2)  # 1 row, 2 columns, 2nd subplot
# plt.title("Follower tracks")
# for i in range(5):
#     plt.plot(foll_dfs[i]['x'], foll_dfs[i]['y'], 'o', label=f"Follower {i}")
#
# plt.plot(avg_foll_df['x'], avg_foll_df['y'], linewidth=5, label='Follower Average')
# plt.grid(True, which='both')
# plt.axhline(y=0, color='k')
# plt.axvline(x=0, color='k')
# plt.xlabel('x')
# plt.ylabel('Vertical offset')
# plt.ylim(-15, 15)
# plt.legend(loc='upper right')
#
# plt.tight_layout()  # Adjust layout for better appearance
plt.show()
