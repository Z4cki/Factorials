CPP=g++
WINCPP=x86_64-w64-mingw32-g++-posix
CFLAGS=-lpthread -lgmp -lgmpxx -std=c++17
WINFLAGS=-I/usr/local/mingw32/include -L/usr/local/mingw32/lib

all: factorial  #factorial.exe

factorial: bin/factorial clean

factorial.exe: bin/factorial.exe clean

bin/factorial: bin/factorial.o
	@$(CPP) bin/factorial.o -o bin/factorial $(CFLAGS)

bin/factorial.o: src/factorial.cpp src/measure_time.h
	@if [ ! -d bin/ ] ; then mkdir bin && echo "created folder bin" ; fi
	@$(CPP) -c src/factorial.cpp -o bin/factorial.o

bin/factorial.exe: bin/factorial.win.o
	@$(WINCPP) $(WINFLAGS) bin/factorial.win.o -o bin/factorial.exe $(CFLAGS)

bin/factorial.win.o: src/factorial.cpp src/measure_time.h
	@if [ ! -d bin/ ] ; then mkdir bin && echo "created folder bin" ; fi
	@$(WINCPP) -c src/factorial.cpp -o bin/factorial.win.o

clean: SHELL:=/bin/bash
clean:
	@rm -r bin/*.o

delete-bin:
	@if [ -d bin/ ]  ; then rm -r bin/ ; fi
	@echo removed all binaries

run:
	@cd bin/ ; ./factorial;