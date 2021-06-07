#include <iostream>

#include "fast_factorial.h"

int main(int argc, char* argv[])
{
    unsigned int num;
    if (argc == 2) // Get command line input..
    {
        num = std::stoi(argv[1]);
    }
    else // .. or ask the user
    {
        printf("Enter number: ");
        scanf("%ud", &num);
    }
    return fastFactorial(num, 1024);
}