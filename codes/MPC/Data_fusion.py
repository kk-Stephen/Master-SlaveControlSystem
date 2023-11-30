# import the csv module
import csv
import os
import pandas as pd

dir_path = "D:/Github/Master-SlaveControlSystem/codes/data/e_v_data"
df = pd.DataFrame()
# open the original csv file
for file in os.listdir(dir_path):
    for data_file in os.listdir(dir_path + "/" + file):
        df_i = pd.read_csv(dir_path + "/" + file + "/" + data_file)
        for i in range(0, 84):
            df_i["e"][i] = df_i["ep"][i + 1]
        df_i = df_i.drop([0, 84])
        df = df.append(df_i)

df["delta_e"] = df["e"] - df["ep"]

df.to_csv("D:/Github/Master-SlaveControlSystem/codes/data/e_v_data/e_v_data.csv")

