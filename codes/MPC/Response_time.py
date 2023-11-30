import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("D:/Github/Master-SlaveControlSystem/codes/data/Rt.csv")

# Extract the columns of interest
y1 = df["left"]
y2 = df["right"]

# Plot the data using matplotlib
plt.plot(y1)
plt.plot(y2)
plt.axhline(y=0.6, color='tomato', linestyle='-.', label="30pwm")
plt.axhline(y=0.22, color='midnightblue', linestyle='-.', label="15pwm")
plt.axvline(x=10, color='black', linestyle=':', label='100ms')
plt.xlabel("t")
plt.ylabel("v")
plt.title("Response time")
plt.legend()
plt.show()

