# Import libraries
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import linregress
import math
import pandas as pd
import os
# Generate some random points around y = 2x
led_df = pd.read_csv(os.path.normpath("D:\Github\Master-SlaveControlSystem\data/accuracy/straight/w_w/leader2.csv"))
x = led_df['x'].to_numpy()
y = led_df['y'].to_numpy()
# x = np.linspace (-5, 5, 10)
# y = 2 * x + np.random.normal (0, 1, 10)

slope = led_df['y'].iat[-1] / led_df['x'].iat[-1]
# foll_coef = foll_df[i]['y'].iat[-1] / foll_df[i]['x'].iat[-1]
# Fit a linear regression model to the points
#slope, intercept, r_value, p_value, std_err = linregress (x, y)

# Calculate the angle of rotation
theta = -math.atan (slope)

# Rotate the points by theta radians around the origin
x_rotated = x * math.cos (theta) - y * math.sin (theta)
y_rotated = x * math.sin (theta) + y * math.cos (theta)

# Plot the original points and the rotated points
plt.plot (x, y, 'bo', label='original points')
plt.plot (x_rotated, y_rotated, 'ro', label='rotated points')
plt.plot (x, slope * x, 'k-', label='regression line')
plt.xlabel ('x')
plt.ylabel ('y')
plt.legend ()
plt.show ()
