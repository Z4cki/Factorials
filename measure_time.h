#ifndef MEASURE_TIME_H_
#define MEASURE_TIME_H_

#include <chrono>
#include <iostream>
#include <string>

typedef std::chrono::_V2::high_resolution_clock clock;
typedef std::chrono::milliseconds millis;

class timer
{
    private:
        std::chrono::time_point<clock> start_time;
        
    public:
        timer()
        {
            start_time = clock::now();
        }
        // "\xC2\xB5" unicode char for micro symbol
        void stop()
        {
            auto end_time = clock::now();
            uint64_t elapsed_time = end_time.time_since_epoch().count() - start_time.time_since_epoch().count();
            if (elapsed_time > 999999999) std::cout << elapsed_time / 1000000.0F << " ms ("  << elapsed_time / 1000000000.0F << " s)" << std::endl;
            else std::cout << elapsed_time / 1000.0F << " \xC2\xB5s ("  << elapsed_time / 1000000.0F << " ms)" << std::endl;
        }

        void stop(const char* msg)
        {
            auto end_time = clock::now();
            uint64_t elapsed_time = end_time.time_since_epoch().count() - start_time.time_since_epoch().count();
            if (elapsed_time > 999999999) std::cout << msg << " " << elapsed_time / 1000000.0F << " ms ("  << elapsed_time / 1000000000.0F << " s)" << std::endl;
            else std::cout << msg << " " << elapsed_time / 1000.0F << " \xC2\xB5s ("  << elapsed_time / 1000000.0F << " ms)" << std::endl;
        }
};
#endif