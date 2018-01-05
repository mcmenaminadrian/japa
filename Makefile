default: all

all: japa

debug: debugjapa

clean:
	rm -f *.o

japa: main.o page.o
	g++ -O2 -o japa -Wall main.o page.o -lexpat -lpthread

main.o: main.cpp page.hpp
	g++ -O2 -o main.o -c -Wall main.cpp

page.o: page.cpp page.hpp
	g++ -O2 -o page.o -c -Wall page.cpp

debugjapa: dmain.o dpage.o
	g++ -g -o japa -Wall dmain.o dpage.o -lexpat -lpthread

dmain.o: main.cpp page.hpp
	g++ -g -o dmain.o -c -Wall main.cpp

dpage.o: page.cpp page.hpp
	g++ -g -o dpage.o -c -Wall page.cpp
