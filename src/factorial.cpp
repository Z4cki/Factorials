#include<iostream>
#include <future>
#include <thread>

#include <gmpxx.h>
#include "measure_time.h"

#ifndef THREADS_COUNT_DEFINED
#define THREADS_COUNT_DEFINED
int iKerne = std::thread::hardware_concurrency();
int threads = std::thread::hardware_concurrency(); //512; //1024; //2048; //4096; // 8192; //16128;
#endif

void CalculateFactorial(std::promise<mpz_class>&& mpzPromise, int start, int end);
void Factorial(int number);
void MergeResult(std::promise<mpz_class>&& mpzPromise, mpz_class a, mpz_class b);

int main()
{
	int number = 1000000;
	Factorial(number);
}

void CalculateFactorial(std::promise<mpz_class>&& mpzPromise, int start, int end)
{
    //debug::db_timer timer;
	mpz_class a = 1;
	for (int i = start; i <= end; i += threads) a *= i;
	mpzPromise.set_value(a);
    //timer.end("Finished split thread");
}

void Factorial(int number)
{
    debug::db_timer timer;
	switch (number)
	{
		case 100000: 
		{
			threads = 64;
			break;
		}
		case 1000000: 
		{
			threads = 512;
			break;
		}
		case 10000000: 
		{
			threads = 4096;
			break;
		}
		case 100000000: 
		{
			threads = 8192;
			break;
		}
		default: 
		{
			threads = 16000;
			break;
		}
	}

	std::promise<mpz_class> factPromise[threads * 2 - 1];
	std::future<mpz_class>  factFuture[threads * 2 - 1];
		
	std::thread factThread[threads * 2];
	for (int i = 0; i < threads; i++)
	{
		factFuture[i] = factPromise[i].get_future();
		factThread[i] = std::thread(CalculateFactorial, std::move(factPromise[i]), i + 1, number);
        factThread[i].detach();
	}
	
    int j = 0;                      
	for (int i = threads; i < threads * 2 - 1; i++)
	{
		factFuture[i] = factPromise[i].get_future();
	    factThread[i] = std::thread(MergeResult, std::move(factPromise[i]), factFuture[j].get(), factFuture[j+1].get());
		j+=2;
        factThread[i].detach();
 	}
    mpz_class result = factFuture[threads * 2 - 2].get();
    timer.end();

    //gmp_printf("%Zd\n", result);
}

void MergeResult(std::promise<mpz_class>&& mpzPromise, mpz_class a, mpz_class b) 
{
	mpzPromise.set_value(a*b);
}