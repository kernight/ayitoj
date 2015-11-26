#! /usr/bin/env python3
import os
import shutil

###备份并清除评测数据

#备份data到back文件夹
dir_data = os.path.join("..","data")
dir_back = os.path.join("..","back")
dir_back_tmp = os.path.join("..","back_tmp")

print("数据文件夹: "+dir_data)
print("备份文件夹: "+dir_back)

print ("正在备份备份")
shutil.copytree(dir_data,dir_back_tmp)

print ("删除原来的备份")
#删除原来的备份
shutil.rmtree(dir_back)

print ("建立新的备份")
#修改文件夹名称
os.rename(dir_back_tmp,dir_back)

print ("正在删除数据")
shutil.rmtree(dir_data)