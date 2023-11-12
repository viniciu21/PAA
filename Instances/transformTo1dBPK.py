import pandas as pd 
import os
import json

base_path = r'/Users/viniciusoliveira/www/Projects/PAA/Instances/original'

folder = os.listdir(base_path)

for file_name in folder: 
    file = open(base_path + "/" + file_name)
    json_file = json.load(file)
    file.close()
    file_name_cleaned = "./instances/1dcleaned/" + file_name.replace("\\", "_").split('.')[0] + ".txt"
    print(file_name_cleaned)
    file_txt = open(file_name_cleaned, 'w')
    
    object_maximuns = json_file["Objects"][0]
    print(object_maximuns)
    max_height = object_maximuns["Height"]
    max_width = object_maximuns["Length"]

    data = json_file["Items"]
    file_txt.write(str(len(data)) + "\n")

    for item in data: 
        print(max_height)
        print(max_width)
        print(item)
        print(item["Height"])

        height = item["Height"] / max_height

        file_txt.write(str(height) + "\n")

    file_txt.close()