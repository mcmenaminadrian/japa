default: all

all: japa

debug: debugjapa

clean:
	rm -f *.o

japa: main.o
	g++ -O2 -o japa -Wall main.o -lexpat

main.o: main.cpp page.hpp
	g++ -O2 -o main.o -Wall main.cpp

debugjapa: dmain.o
	g++ -g -o japa -Wall dmain.o -lexpat

dmain.o: main.cpp page.hpp
	g++ -g -o dmain.o -Wall main.cpp
