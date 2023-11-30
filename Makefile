CFLAGS = -g -Wall -std=c++11 
#CFLAGS = -g -std=c++11 
#CFLAGS = -g -std=c++11 -Wdelete-non-abstract-non-virtual-dtor
CC = g++
BIN =  main
HFILES = vec3.h  \
		 color.h

# targets
all : $(BIN) 

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): %: %.o  $(HFILES)
	$(CC) $(CFLAGS) $@.o -o $@

clean :
	-rm -f a.out *.o core atest *.out
	-rm -f *.class
	-rm -f $(BIN)
	-rm -f *.ppm

run :
	./$(BIN) > out.ppm
