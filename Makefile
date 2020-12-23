output: main.o
	g++ main.o -o bin/main

main.o: main.cpp measure_time.h
	g++ main.cpp -c -pthread -lgmp -lgmpxx -std=c++17

clean:
	rm *.o