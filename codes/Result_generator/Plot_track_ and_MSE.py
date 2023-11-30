import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np
from scipy.stats import linregress
import math

led_files = []
foll_files = []
for i in range(5):
    led = os.path.normpath("D:\Github\Master-SlaveControlSystem\data/accuracy/straight/b_b" + "/leader" + str(i) + ".csv")
    foll = os.path.normpath("D:\Github\Master-SlaveControlSystem\data/accuracy/straight/b_b" + "/follower" + str(i) + ".csv")
    led_files.append(led)
    foll_files.append(foll)
# led_files.append(os.path.normpath("D:\Github\Master-SlaveControlSystem\data/accuracy/straight/p_b/leader_average.csv"))
# foll_files.append(os.path.normpath("D:\Github\Master-SlaveControlSystem\data/accuracy/straight/p_b/follower_average.csv"))
print(led_files)


led_df = []
foll_df = []
led_mse = []
foll_mse = []
for i in range(5):
    print(i)
    led_df.append(pd.read_csv(led_files[i]))
    foll_df.append(pd.read_csv(foll_files[i]))
    # led_coef = led_df[i]['y'].iat[-1] / led_df[i]['x'].iat[-1]
    # foll_coef = foll_df[i]['y'].iat[-1] / foll_df[i]['x'].iat[-1]
    # led_df[i]['y'] = led_df[i]['y'].apply(lambda y: y - led_coef * led_df[i]['x'])
    # foll_df[i]['y'] = foll_df[i]['y'].apply(lambda y: y - foll_coef * foll_df[i]['x'])
    led_x = led_df[i]['x'].to_numpy()
    led_y = led_df[i]['y'].to_numpy()
    slope, intercept, r_value, p_value, std_err = linregress(led_x, led_y)
    # Calculate the angle of rotation
    led_theta = -math.atan(slope)
    for index, row in led_df[i].iterrows():
        # Update the column y value by subtracting the product of led_coef and column x value
        x = led_df[i].at[index, 'x']
        y = led_df[i].at[index, 'y']
        led_df[i].at[index, 'y'] = x * math.cos(led_theta) - y * math.sin(led_theta)
        led_df[i].at[index, 'x'] = x * math.sin(led_theta) + y * math.cos(led_theta)

    foll_x = foll_df[i]['x'].to_numpy()
    foll_y = foll_df[i]['y'].to_numpy()
    slope, intercept, r_value, p_value, std_err = linregress(led_x, led_y)
    # Calculate the angle of rotation
    foll_theta = -math.atan(slope)
    for index, row in foll_df[i].iterrows():
        # Update the column y value by subtracting the product of led_coef and column x value
        x = foll_df[i].at[index, 'x']
        y = foll_df[i].at[index, 'y']
        foll_df[i].at[index, 'y'] = x * math.cos(foll_theta) - y * math.sin(foll_theta)
        foll_df[i].at[index, 'x'] = x * math.sin(foll_theta) + y * math.cos(foll_theta)

    led_mse.append(np.mean(np.square(led_df[i]['x'])))
    foll_mse.append(np.mean(np.square(foll_df[i]['x'])))
    plt.plot(led_df[i]['x'], led_df[i]['y'], 'o')
    plt.plot(foll_df[i]['x'], foll_df[i]['y'], 'o')

# r = led_df[0].shape[0]
# avg_df = pd.DataFrame(index=range(r), columns=["theta", "x", "y"])
#
# for r in range(r):
#     for c in range(3):
#         value = 0
#         for i in range(5):
#             value = value + led_df[i].iloc[r, c]
#         avg_df.iat[r, c] = value / 5
#
# print(avg_df.head())
# plt.plot(avg_df['y'], avg_df['x'])

plt.hlines(y=0, xmin=0, xmax=810, color='black', linestyle='-.', linewidth=5)
plt.xlabel('x')
plt.ylabel('y')
plt.show()

