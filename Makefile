CC = gcc -g3
CCC = g++ -g3

all :luatest.out 

%.o : %.c 
	$(CC) -c -o $@ $< 

%.o : %.cpp
	$(CCC) -c -o $@ $< 

luatest.out : luatest.o luabindfunc.o
	$(CC)  -Wl,-E -o $@ $^ -ldl -lrt -Wl,-E -llua -lm

seanlab.so : luabindfunc.c
	gcc -Wall -g -fPIC --shared $^ -o $@ 
	
clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf *.so

























