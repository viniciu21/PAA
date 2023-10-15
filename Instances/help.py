import pandas as pd 
import os
import json

base_path = r'/Users/viniciusoliveira/www/Projects/PAA/Instances/cleaned'

folder = os.listdir(base_path)

for file_name in folder:
    os.rename(file_name, file_name.replace("\/", "_"))