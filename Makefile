CPP:=g++
PKGCONFIG:=$(shell which pkg-config)
CFLAGS:=-g -std=c++17 -Wall -lpthread \
		$(shell $(PKGCONFIG) --cflags gmpxx) \
		$(shell $(PKGCONFIG) --libs gmpxx)

SRC:=main.cpp \
	fast_factorial.cpp

RM:=rm -rf

all: factorial

factorial: $(SRC)
	$(CPP) -o $@ $^ $(CFLAGS)

clean:
	$(RM) factorial
	$(RM) *.o