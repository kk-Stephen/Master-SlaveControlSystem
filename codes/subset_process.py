import pandas as pd
import os
import math
import numpy as np

dir_path_L = "D:/Github/Master-SlaveControlSystem/straight_L.txt"
dir_path_R = "D:/Github/Master-SlaveControlSystem/straight_R.txt"

df_L = pd.read_csv(dir_path_L, header=None, names=["theta", "x", "y"])
df_F = pd.read_csv(dir_path_R, header=None, names=["theta", "x", "y"])
df = [df_L, df_F]
n = len(df_L)

for i in range(2):
    led_x = df[i]['x'].to_numpy()
    led_y = df[i]['y'].to_numpy()
    led_coef = df[i]['y'].iat[-1] / df[i]['x'].iat[-1]
    led_theta = -math.atan(led_coef)

    R = np.array([[math.cos(led_theta), -math.sin(led_theta)], [math.sin(led_theta), math.cos(led_theta)]])
    points_vector = np.vstack([led_x, led_y])
    rotated_points_vector = np.dot(R, points_vector)
    x_rotated, y_rotated = rotated_points_vector[0], rotated_points_vector[1]
    df[i]['x'] = x_rotated
    df[i]['y'] = y_rotated

    df[i].to_csv(f"D:/Github/Master-SlaveControlSystem/straight{i}.csv")