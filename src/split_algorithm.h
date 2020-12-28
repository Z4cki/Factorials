#ifndef SPLIT_ALGORITHM_H
#define SPLIT_ALGORITHM_H

#include <future>
#include <thread>

#include <gmpxx.h>

#ifndef THREADS_COUNT_DEFINED
#define THREADS_COUNT_DEFINED
int threads = std::thread::hardware_concurrency();
int iKerne = 8;

void MergeResult(std::promise<mpz_class>&& mpzPromise, mpz_class a, mpz_class b) 
{
	mpzPromise.set_value(a*b);
}
#endif

void CalculateFactorial2(std::promise<mpz_class>&& mpzPromise, int iStart, int iF, int nCores);
void Factorial2(int number);
void PartialResult(mpz_class *f, int iStart, int iF, int nThread);

void CalculateFactorial2(std::promise<mpz_class>&& mpzPromise, int iStart, int iF, int nCores)
{
	int iSplit = nCores / iKerne;
	int nThread = nCores;
	int iAnf = (iStart-1) *iSplit +1;
	mpz_class f[iSplit*2-1];
	for (int i = 0; i < iSplit; i++) PartialResult(&f[i], iAnf+i, iF, nThread);
	
	int j = 0;
	for (int i = iSplit; i< 2*iSplit - 1; i++) 
	{
			f[i] = f[j] * f[j+1];
			j +=2;
	}
	
	mpzPromise.set_value(f[iSplit*2-2]);
 
	printf("Thread %d finished in ", iStart);
 
}

void Factorial2(int number)
{
	mpz_class result = 1;

	std::promise<mpz_class> promiseFak[threads*2-1];

	std::future<mpz_class> fakResult[threads*2-1];
		
	std::thread fakThread[threads*2-1];
	int i = 0;
	for (int i = 0; i < (int)threads; i++)
	{

		fakResult[i] = promiseFak[i].get_future();
		fakThread[i] = std::thread(CalculateFactorial2, std::move(promiseFak[i]), i + 1, number, (int)threads);
	}

	int j = 0;
	for (int i = (int)threads; i < (int)threads*2-1; i++) 
	{
		fakResult[i] = promiseFak[i].get_future();
		fakThread[i]= std::thread(MergeResult, std::move(promiseFak[i]), fakResult[j].get(), fakResult[j+1].get(), i+1);
		j +=2;
	}

	for (int i = 0; i < 2*(int)threads-1; i++)fakThread[i].join();
	result = fakResult[2*threads-2].get();

	printf("Calculate result in ");//, i + 1);
}

void PartialResult(mpz_class *f, int iStart, int iF, int nThread)
{
	*f = 1;
	for (int i = iStart; i <= iF; i+= nThread) *f *= i;
}

#endif