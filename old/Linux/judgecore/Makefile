o_object = src/config.o src/log.o src/database.o src/function.o src/compile.o src/sandbox.o src/outjudge.o  src/main.o 
l_object = -L/usr/lib/ -lmysqlpp -lmysqlclient
p_object = -std=c++11
log_object = log/Error/*.log log/Judge/*.log log/Normal/*.log 

judgecore:$(o_object)
	g++  $(p_object) -o judgecore $(o_object)  $(l_object)

main.o: 	src/main.cpp 		include/head.h
function.o: 	src/function.cpp 	include/function.h 	include/head.h
log.o: 		src/log.cpp 		include/log.h 		include/head.h
config.o: 	src/config.cpp 		include/config.h 	include/head.h
database.o: 	src/database.cpp 	include/database.h 	include/head.h
compile.o: 	src/compile.cpp 	include/compile.h 	include/head.h
sandbox.o: 	src/sandbox.cpp 	include/sandbox.h 	include/head.h
outjudge.o: 	src/outjudge.cpp 	include/outjudge.h 	include/head.h

.PHONY:clean
clean:
	-rm judgecore $(o_object) $(log_object)