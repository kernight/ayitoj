#! /usr/bin/env python3
import os
import shutil

###从备份恢复评测数据

#备份data到back文件夹
dir_data = os.path.join("..","data")
dir_back = os.path.join("..","back")

print("数据文件夹: "+dir_data)
print("备份文件夹: "+dir_back)

print ("正在恢复备份")
shutil.copytree(dir_back,dir_data)
