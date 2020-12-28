#ifndef MEASURE_TIME_H
#define MEASURE_TIME_H

#include <chrono>
#include <iostream>
#include <string>

namespace debug 
{
    typedef std::chrono::_V2::high_resolution_clock clock;
    typedef std::chrono::milliseconds millis;

    class db_timer
    {
        private:
            std::chrono::time_point<clock> start_time;
            
        public:
            db_timer()
            {
                start_time = clock::now();
            }
            // "\xC2\xB5" unicode char for micro symbol
            void end()
            {
                auto end_time = clock::now();
                uint64_t measured_time = end_time.time_since_epoch().count() - start_time.time_since_epoch().count();
                if (measured_time > 999999999) std::cout << measured_time / 1000000.0F << " ms ("  << measured_time / 1000000000.0F << " s)" << std::endl;
                else std::cout << measured_time / 1000.0F << " \xC2\xB5s ("  << measured_time / 1000000.0F << " ms)" << std::endl;
            }

            void end(const char* msg)
            {
                auto end_time = clock::now();
                uint64_t measured_time = end_time.time_since_epoch().count() - start_time.time_since_epoch().count();
                if (measured_time > 999999999) std::cout << msg << " " << measured_time / 1000000.0F << " ms ("  << measured_time / 1000000000.0F << " s)" << std::endl;
                else std::cout << msg << " " << measured_time / 1000.0F << " \xC2\xB5s ("  << measured_time / 1000000.0F << " ms)" << std::endl;
            }
    };
}
#endif