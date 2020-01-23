#链接 -lpthread 进行编译
thread : thread.o
	cc -Wall -o thread thread.o -lpthread
thread.o : thread.c
	cc -c thread.c

.PHONY : clean
clean : 
	rm thread *.o
