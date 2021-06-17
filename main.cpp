#include <iostream>

#include "factorial_fast.hpp"

int main(int argc, char* argv[])
{
    unsigned int num;
    if (argc == 2) // Get command line input ..
    {
        num = std::stoi(argv[1]);
    }
    else // .. or ask the user
    {
        printf("Enter number: ");
        scanf("%ud", &num);
    }
    double timer;
    int status = fastFactorial(num, 1024, &timer);
    printf("Elapsed time: %.2f ms\n", timer);
    return status;
}