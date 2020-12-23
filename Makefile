bin/factorial: bin/factorial.o
	g++ bin/factorial.o -o bin/factorial -pthread -lgmp -lgmpxx -std=c++17

bin/factorial.o: src/factorial.cpp src/measure_time.h
	mkdir -p bin
	g++ -c src/factorial.cpp -o bin/factorial.o

clean:
	rm bin/*.o