CPP=g++
WINCPP=x86_64-w64-mingw32-g++-posix
CFLAGS=-lpthread -lgmp -lgmpxx -std=c++17
WINFLAGS=-I/usr/local/include -L/usr/local/lib


all: bin/factorial bin/factorial.exe

factorial: bin/factorial

factorial.exe: bin/factorial.exe

bin/factorial: bin/factorial.o
	$(CPP) bin/factorial.o -o bin/factorial $(CFLAGS)

bin/factorial.o: src/factorial.cpp src/measure_time.h
	@if [ ! -d bin/ ] ; then mkdir bin && echo "created folder bin" ; fi
	$(CPP) -c src/factorial.cpp -o bin/factorial.o

bin/factorial.exe: bin/factorial.win.o
	$(WINCPP) $(WINFLAGS) bin/factorial.win.o -o bin/factorial.exe $(CFLAGS)

bin/factorial.win.o: src/factorial.cpp src/measure_time.h
	@if [ ! -d bin/ ] ; then mkdir bin && echo "created folder bin" ; fi
	$(WINCPP) $(WINFLAGS) src/factorial.cpp -o bin/factorial.win.o $(CFLAGS)
	
clean:
	@if [ -f bin/*.o ] ; then rm bin/*.o ; fi
	@echo cleanup succesfull

delete-bin:
	@if [ -d bin/ ]  ; then rm -r bin/ ; fi
	@echo removed all binaries

run:
	@cd bin/ ; ./factorial;