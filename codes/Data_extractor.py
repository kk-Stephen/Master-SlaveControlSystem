# import the csv module
import csv
import os

dir_path = "D:/Github/Master-SlaveControlSystem/codes/data/e_v_data"
# open the original csv file
for file in os.listdir(dir_path):
    if file.endswith(".txt"):
        file_name = file[:-4]
        print(file_name)
        with open(os.path.join(dir_path, file), "r") as f:
            # create a csv reader object
            reader = csv.reader(f)
            dir_path1 = dir_path + "/" + file_name + "/"
            os.mkdir(dir_path1)
            # create two csv writer objects for the two output files
            writer1 = csv.writer(open(dir_path1 + file_name + "_1.csv", "w", newline=""))
            writer2 = csv.writer(open(dir_path1 + file_name + "_2.csv", "w", newline=""))
            writer3 = csv.writer(open(dir_path1 + file_name + "_3.csv", "w", newline=""))
            writer4 = csv.writer(open(dir_path1 + file_name + "_4.csv", "w", newline=""))
            writer_list = iter([writer1, writer2, writer3, writer4])
            # loop through the rows of the original csv file
            writer = next(writer_list)
            writer.writerow(["ep", "vl", "vr", "e"])
            for row in reader:
                # check if the row contains *****
                if row[0] == "***********":
                    # switch to the second output file
                    if writer == writer4:
                        break
                    writer = next(writer_list)
                    writer.writerow(["ep", "vl", "vr", "e"])
                else:
                    # write the row to the current output file
                    writer.writerow(row)
