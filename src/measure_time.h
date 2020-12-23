#include <chrono>
#include <iostream>

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
            void end()
            {
                auto end_time = clock::now();
                auto measured_time = end_time.time_since_epoch().count() - start_time.time_since_epoch().count();
                std::cout << measured_time / 1000.0F << " \xC2\xB5s ("  << measured_time / 1000000.0F << " ms)" << std::endl;
            }

            void end(const char* msg)
            {
                auto end_time = clock::now();
                auto measured_time = end_time.time_since_epoch().count() - start_time.time_since_epoch().count();
                std::cout << msg << " " << measured_time / 1000.0F << " \xC2\xB5s ("  << measured_time / 1000000.0F << " ms)" << std::endl;
            }
    };
}