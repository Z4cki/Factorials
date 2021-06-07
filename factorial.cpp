#include <iostream>
#include <future>
#include <thread>

#include <gmpxx.h>
#include "measure_time.h"

#ifndef THREAD_COUNT
#define THREAD_COUNT
const unsigned int physicalThreads = std::thread::hardware_concurrency();
#endif

void CalculateFactorial(std::promise<mpz_class>&& mpzPromise, int start, int end, int threads);
void Factorial(int number);
void MergeResult(std::promise<mpz_class>&& mpzPromise, std::future<mpz_class>* a, std::future<mpz_class>* b);

int main1()
{
	int number;
	std::cout << "Number: ";
	std::cin >> number;
	Factorial(number);
	return 0;
}

void CalculateFactorial(std::promise<mpz_class>&& mpzPromise, int start, int end, int threads)
{
    //debug::db_timer timer;
	mpz_class a = 1;
	for (int i = start; i <= end; i += threads) a *= i;
	mpzPromise.set_value(a);
    //timer.end("Finished split thread");
}

void Factorial(int number)
{
	if (number <= 1) 
	{
		std::cout << "Nothing to do.\n";
		return;
	}
    timer timer;
	int threads; //512; //1024; //2048; //4096; // 8192; //16128;
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
			threads = 8192;
			break;
		}
		case 100000000: 
		{
			threads = 64000;
			break;
		}
		default: 
		{
			if (number < 100000) threads = physicalThreads;
			else threads = 32000;
			if (threads > number) threads = number;
			break;
		}
	}

	std::promise<mpz_class> promisePool[threads * 2 - 1];
	std::future <mpz_class> futurePool [threads * 2 - 1];
		
	std::thread threadPool[threads * 2];
	for (int i = 0; i < threads; i++)
	{
		futurePool[i] = promisePool[i].get_future();
		threadPool[i] = std::thread(CalculateFactorial, std::move(promisePool[i]), i + 1, number, threads);
        threadPool[i].detach();
	}
	
    int j = 0;                      
	for (int i = threads; i < threads * 2 - 1; i++)
	{
		futurePool[i] = promisePool[i].get_future();
	    threadPool[i] = std::thread(MergeResult, std::move(promisePool[i]), &futurePool[j], &futurePool[j+1]);
		j+=2;
        threadPool[i].detach();
 	}
    mpz_class result = futurePool[threads * 2 - 2].get();
    timer.stop();

    //gmp_printf("%Zd\n", result);
}

void MergeResult(std::promise<mpz_class>&& mpzPromise, std::future<mpz_class>* a, std::future<mpz_class>* b) 
{
	mpzPromise.set_value(a->get() * b->get());
}