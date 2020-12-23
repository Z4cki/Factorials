factorial: factorial.o
	g++ factorial.o -o bin/factorial

factorial.o: factorial.cpp measure_time.h
	g++ factorial.cpp -c -pthread -lgmp -lgmpxx -std=c++17

clean:
	rm *.o