import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np
import math

main_dir = 'D:/Github/Master-SlaveControlSystem/data/accuracy/straight/b/'
avg_foll_dfs = []
led_dfs = []
sys = []
for foll_file in os.listdir(main_dir):
    sys.append(foll_file)
    files = os.path.join(main_dir, foll_file) + '/'
    foll_df = pd.read_csv(os.path.join(files, 'follower_average.csv'))
    avg_foll_dfs.append(foll_df)
    for i in range(5):
        led = os.path.join(files, f"leader{i}.csv")
        led_df = pd.read_csv(led)
        led_dfs.append(led_df)

avg_led_df = pd.concat(led_dfs).groupby(level=0).mean()
plt.plot(avg_led_df['x'], avg_led_df['y'], linewidth=5, label='Leader ')
for i in range(3):
    plt.plot(avg_foll_dfs[i]['x'], avg_foll_dfs[i]['y'], 'o', label="Follower " + sys[i])

plt.grid(True, which='both')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.xlabel('x')
plt.ylabel('Vertical offset')
plt.ylim(-15, 15)
plt.legend(loc='upper right')
plt.show()
