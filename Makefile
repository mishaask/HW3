all: StrList libStrList.a

StrList:main.o libStrList.a
	gcc -Wall -g -o StrList main.o StrList.o libStrList.a

main.o: main.c StrList.h
	gcc -c main.c

StrList.o: StrList.c StrList.h
	gcc -c StrList.c

libStrList.a: StrList.o
	ar -rcs libStrList.a StrList.o
	ranlib libStrList.a

.PHONY: clean all

clean:
	rm -f *.o *.a StrList