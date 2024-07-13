#pragma once

#ifndef EXECUTION_TIMER_H
#define EXECUTION_TIMER_H

#include <chrono>

class Timer {
public:
    // set start time on instance creation
    Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

    // reset start time to current time
    void reset() {
        start_time_ = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        std::chrono::duration<double> elapsed_time = std::chrono::high_resolution_clock::now() - start_time_;
        return elapsed_time.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
};

#endif // EXECUTION_TIMER_H
