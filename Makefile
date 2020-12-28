CPP=g++
WINCPP=x86_64-w64-mingw32-g++-posix
CFLAGS=-lpthread -lgmp -lgmpxx -std=c++17
WINFLAGS=-static -static-libgcc -static-libstdc++ -I/usr/local/mingw32/include -L/usr/local/mingw32/lib

all: factorial  #factorial.exe

factorial: bin/factorial clean

factorial.exe: bin/factorial.exe clean

# create linux executable 
bin/factorial: bin/factorial.o
	@$(CPP) bin/factorial.o -o bin/factorial $(CFLAGS)

# create win executable 
bin/factorial.exe: bin/factorial.win.o
	@$(WINCPP) $(WINFLAGS) bin/factorial.win.o -o bin/factorial.exe $(CFLAGS)

# compile linux object file 
bin/factorial.o: src/factorial.cpp src/measure_time.h
	@if [ ! -d bin/ ] ; then mkdir bin && echo "created folder bin" ; fi
	@$(CPP) -c -g src/factorial.cpp -o bin/factorial.o

# compile win object file 
bin/factorial.win.o: src/factorial.cpp src/measure_time.h
	@if [ ! -d bin/ ] ; then mkdir bin && echo "created folder bin" ; fi
	@$(WINCPP) -c -g src/factorial.cpp -o bin/factorial.win.o

clean: SHELL:=/bin/bash
clean:
	@rm -r bin/*.o

delete-bin:
	@if [ -d bin/ ]  ; then rm -r bin/ ; fi
	@echo removed all binaries

run:
	@cd bin/ ; ./factorial;