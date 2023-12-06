import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np
import math

main_dir_b = 'D:/Github/Master-SlaveControlSystem/data/accuracy/straight/b/'
main_dir_w = 'D:/Github/Master-SlaveControlSystem/data/accuracy/straight/w/'
main_dir_p = 'D:/Github/Master-SlaveControlSystem/data/accuracy/straight/p/'
main_dirs = [main_dir_b, main_dir_w, main_dir_p]
avg_foll_dfs = [[], [], []]
led_dfs = []
sys = [[], [], []]
for j in range(3):
    main_dir = main_dirs[j]
    dfs = []
    for foll_file in os.listdir(main_dir):
        sys[j].append(foll_file)
        files = os.path.join(main_dir, foll_file) + '/'
        foll_df = pd.read_csv(os.path.join(files, 'follower_average.csv'))
        avg_foll_dfs[j].append(foll_df)
        for i in range(5):
            led = os.path.join(files, f"leader{i}.csv")
            led_df = pd.read_csv(led)
            dfs.append(led_df)
    avg_led_df = pd.concat(dfs).groupby(level=0).mean()
    led_dfs.append(avg_led_df)


plt.figure(figsize=(13, 10))
plt.subplot(3, 1, 1)
#plt.plot(avg_led_df['x'], avg_led_df['y'], linewidth=5, label='Leader ')
plt.title("Average tracks of Bang-Bang leader and its followers")
plt.plot(led_dfs[0]['x'], led_dfs[0]['y'], label='Leader ')
print(led_dfs[0]['x'].iloc[-1])
for i in range(3):
    plt.plot(avg_foll_dfs[0][i]['x'], avg_foll_dfs[0][i]['y'], '-.', label="Follower " + sys[0][i])

plt.grid(True, which='both')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.xlabel('Horizontal distance (mm)')
plt.ylabel('Vertical offset (mm)')
plt.ylim(-10, 10)
plt.legend(loc='upper right')

plt.subplot(3, 1, 2)
plt.title("Average tracks of Weighted leader and its followers")
plt.plot(led_dfs[1]['x'], led_dfs[1]['y'], label='Leader ')
print(led_dfs[1]['x'].iloc[-1])
for i in range(3):
    plt.plot(avg_foll_dfs[1][i]['x'], avg_foll_dfs[1][i]['y'], '-.', label="Follower " + sys[1][i])

plt.grid(True, which='both')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.xlabel('Horizontal distance (mm)')
plt.ylabel('Vertical offset (mm)')
plt.ylim(-10, 10)
plt.legend(loc='upper right')

plt.subplot(3, 1, 3)
plt.title("Average tracks of PID leader and its followers")
plt.plot(led_dfs[2]['x'], led_dfs[2]['y'], label='Leader ')
print(led_dfs[2]['x'].iloc[-1])
for i in range(3):
    plt.plot(avg_foll_dfs[2][i]['x'], avg_foll_dfs[2][i]['y'], '-.', label="Follower " + sys[2][i])
plt.grid(True, which='both')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.xlabel('Horizontal distance (mm)')
plt.ylabel('Vertical offset (mm)')
plt.ylim(-10, 10)
plt.legend(loc='upper right')

plt.tight_layout()
plt.show()
