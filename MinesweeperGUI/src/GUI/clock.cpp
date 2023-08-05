#include "GUI/clock.hpp"
using namespace std::chrono;

namespace gui::util
{
    void clock::start() {
        if (timing_) throw clock_exception("timer already started");
        start_time_ = steady_clock::now();
        timing_ = true;
    }

    long long clock::get_elapsed_time() const {
        return timing_ ? duration_cast<milliseconds>(steady_clock::now() - start_time_).count()+elapsed_time_ : elapsed_time_;
    }

    void clock::set_time(long long time)
    {
        elapsed_time_ = time;
    }

    void clock::stop() {
        if (!timing_) throw clock_exception("timer hasn't started yet");
        elapsed_time_ = get_elapsed_time();
        timing_ = false;
    }

    void clock::clear()
    {
        elapsed_time_ = 0;
        start_time_ = steady_clock::now();
    }

    bool clock::is_timing() const {
        return timing_;
    }

    void clock::reset()
    {
        timing_ = false;
        elapsed_time_ = 0;
    }
}


