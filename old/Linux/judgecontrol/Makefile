o_object = src/config.o src/log.o src/database.o src/function.o  src/main.o 
l_object = -L/usr/lib/ -lmysqlpp -lmysqlclient
p_object = -std=c++11

judgecontrol:$(o_object)
	g++  $(p_object) -o judgecontrol $(o_object)  $(l_object)

main.o: 	src/main.cpp 		include/head.h
function.o: 	src/function.cpp 	include/function.h 	include/head.h
log.o: 		src/log.cpp 		include/log.h 		include/head.h
config.o: 	src/config.cpp 		include/config.h 	include/head.h
database.o: 	src/database.cpp 	include/database.h 	include/head.h


.PHONY:clean
clean:
	-rm judgecontrol $(o_object) 