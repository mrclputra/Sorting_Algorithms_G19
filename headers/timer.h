#pragma once

#ifndef EXECUTION_TIMER_H
#define EXECUTION_TIMER_H

#include <chrono>

class timer {
public:
    timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

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
