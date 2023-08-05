#pragma once
#ifndef __CLOCK_H_
#define __CLOCK_H_

#include<chrono>
#include <exception>
namespace gui::util
{
    class clock final
    {
    public:
        void start();
        void stop();
        void clear();
        void reset();
        bool is_timing() const;
        long long get_elapsed_time() const;
        void set_time(long long time);
    private:
        std::chrono::time_point<std::chrono::steady_clock> start_time_;
        bool timing_ = false;
        long long elapsed_time_ = 0;
    };

    class clock_exception : public std::exception
    {
    public:
        clock_exception(const char* error_msg) : std::exception(error_msg){}
    };
}

#endif