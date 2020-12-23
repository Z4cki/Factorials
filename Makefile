bin/factorial: bin/factorial.o
	g++ bin/factorial.o -o bin/factorial -pthread -lgmp -lgmpxx -std=c++17

bin/factorial.o: src/factorial.cpp src/measure_time.h
	@if [ ! -d bin/ ] ; then mkdir bin && echo "created folder bin" ; fi
	g++ -c src/factorial.cpp -o bin/factorial.o

clean:
	@if [ -f bin/*.o ] ; then rm bin/*.o ; fi
	@echo cleanup succesfull

delete-bin:
	@if [ -f bin/*.* ] ; then rm bin/* ; fi
	@if [ -d bin/ ]  ; then rmdir bin/ ; fi
	@echo removed all binaries