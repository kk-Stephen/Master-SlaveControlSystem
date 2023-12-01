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
        "D:\Github\Master-SlaveControlSystem\data/accuracy/straight/b_b" + "/leader" + str(i) + ".csv")
    foll = os.path.normpath(
        "D:\Github\Master-SlaveControlSystem\data/accuracy/straight/b_b" + "/follower" + str(i) + ".csv")
    led_files.append(led)
    foll_files.append(foll)

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

    led_mse.append(np.mean(np.square(led_df['x'])))
    foll_mse.append(np.mean(np.square(foll_df['x'])))

    # Append DataFrames to the list for later averaging
    led_dfs.append(led_df)
    foll_dfs.append(foll_df)

    plt.plot(led_df['x'], led_df['y'], 'o')
    plt.plot(foll_df['x'], foll_df['y'], 'o')

# Calculate average DataFrames
avg_led_df = pd.concat(led_dfs).groupby(level=0).mean()
avg_foll_df = pd.concat(foll_dfs).groupby(level=0).mean()
plt.plot(avg_led_df['x'], avg_led_df['y'], linewidth=5, label='leader average')
plt.plot(avg_foll_df['x'], avg_foll_df['y'], linewidth=5, label='follower average')
plt.hlines(y=0, xmin=0, xmax=810, color='black', linestyle='-.', linewidth=5)
plt.xlabel('x')
plt.ylabel('y')
plt.ylim(-15, 15)
plt.legend(loc='upper right')
plt.show()
