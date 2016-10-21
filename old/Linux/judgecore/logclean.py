#! /usr/bin/env python3
import os
import shutil

###清除日志文件

#备份data到back文件夹
dir_data = os.path.join("..","data")
dir_log = os.path.join(dir_data,"log")
dir_log_Error = os.path.join(dir_log,"Error")
dir_log_judge = os.path.join(dir_log,"Judge")
dir_log_Normal = os.path.join(dir_log,"Normal")

print ("执行删除"+dir_log_Error)
shutil.rmtree(dir_log_Error)

print ("执行删除"+dir_log_judge)
shutil.rmtree(dir_log_judge)

print ("执行删除 "+dir_log_Normal)
shutil.rmtree(dir_log_Normal)

print ("重建目录")
os.mkdir(dir_log_Error)
os.mkdir(dir_log_judge)
os.mkdir(dir_log_Normal)


