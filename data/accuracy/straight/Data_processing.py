import pandas as pd
import os
import csv

dir_path = "D:/Github/Master-SlaveControlSystem/data/accuracy/curve"
# open the original csv file
folders = [f for f in os.listdir(dir_path) if os.path.isdir(os.path.normpath(os.path.join(dir_path, f)))]
for file in os.listdir(dir_path):
    if os.path.isdir(os.path.normpath(os.path.join(dir_path, file))):
        for data_file in os.listdir(os.path.normpath(os.path.join(dir_path, file))):
            with open(os.path.normpath(os.path.join(os.path.join(dir_path, file), data_file)), "r") as input:
                # Read the file content as a list of lines
                lines = input.readlines()
            # Open the file in write mode
            with open(os.path.normpath(os.path.join(os.path.join(dir_path, file), data_file)), "w") as output:
                # Loop through each line
                for line in lines:
                    # Check if the line contains the substring "***********"
                    if "***********" not in line:
                        # Write the line to the output file
                        output.write(line)
            df = pd.read_csv(os.path.normpath(os.path.join(os.path.join(dir_path, file), data_file)), header=None, names=["theta", "x", "y"])
            n = len(df)
            k = n // 5
            sub_ds = []
            for i in range(5):
                # Get the start and end index of the sub dataframe
                start = i * k
                end = (i + 1) * k
                # Slice the dataframe by the index
                sub_df = df.iloc[start:end]
                # Print the sub dataframe
                #print(f"Sub dataframe {i+1}:")
                #print(sub_df)
                #file_name = os.path.normpath(os.path.join(os.path.join(dir_path, file), "/" + data_file + str(i) + ".csv"))
                file_name = os.path.normpath(os.path.join(os.path.join(dir_path, file)) + "/" + data_file + str(i) + ".csv")
                print(file_name)
                sub_df.to_csv(file_name, encoding='utf-8')
                sub_ds.append(sub_df)

            avg_df = sub_df
            for r in range(k):
                for c in range(3):
                    value = 0
                    for i in range(5):
                        value = value + sub_ds[i].iloc[r, c]
                    avg_df.iat[r, c] = value / 5

            file_name = os.path.normpath(os.path.join(os.path.join(dir_path, file)) + "/" + data_file + "_average.csv")
            avg_df.to_csv(file_name, encoding='utf-8')
            # print("avg_df-sub_df")
            # print(avg_df)




