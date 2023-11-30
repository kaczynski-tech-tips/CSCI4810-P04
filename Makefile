CFLAGS = -g -Wall -std=c++11 
#CFLAGS = -g -std=c++11 
#CFLAGS = -g -std=c++11 -Wdelete-non-abstract-non-virtual-dtor
CC = g++
LDFLAGS =

BIN =  main_simple	

HFILES = color.h 	\
	ray.h 		\
	rtweekend.h 	\
	vec3.h

# targets
all: $(BIN) 

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@ 

$(BIN): %: %.o  $(HFILES)
	$(CC) $(CFLAGS) $@.o -o $@  $(LDFLAGS)

clean :
	-rm -f a.out *.o core atest *.out 
	-rm -f *.class
	-rm -f  $(BIN)
	-rm -f *.ppm

allclean :
	-rm -f a.out *.o core atest *.out 
	-rm -f *.class
	-rm -f *.ppm
	-rm -f  $(BIN)

run : 
	./$(BIN) > out.ppm
