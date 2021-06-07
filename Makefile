CPP:=g++
PKGCONFIG:=$(shell which pkg-config)
CFLAGS:=-g -std=c++17 -Wall -lpthread \
		$(shell $(PKGCONFIG) --cflags gmpxx) \
		$(shell $(PKGCONFIG) --libs gmpxx)

SRC:=main.cpp \
	fast_factorial.cpp

BENCH:=test.cpp \
	benchmark.cpp \
	fast_factorial.cpp

RM:=rm -rf

all: factorial benchmark

factorial: $(SRC)
	@echo Compiling $@ ..
	@$(CPP) -o $@ $^ $(CFLAGS)
	@echo "Done\n"

benchmark: $(BENCH)
	@echo Compiling $@ ..
	@$(CPP) -o $@ $^ $(CFLAGS)
	@echo "Done\n"

clean:
	$(RM) benchmark
	$(RM) factorial
	$(RM) *.o