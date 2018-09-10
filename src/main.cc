#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>

#include "fibonacci.h"

using namespace edu::sbcc::cs140;
using std::chrono::system_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

static constexpr uint32_t TEST_ITERATIONS = 1000;
static constexpr uint32_t FIBONACCI_NUMBER = 44;

template<typename T>
uint64_t measureExecTime(const std::function<void(void)> &measured);

int main() {
    static FibonacciSolver *solvers[] = {
            new RecursiveFibonacciSolver,
            new DynamicFibonacciSolver,
#ifdef SUPPORTS_CLOSED_FORM
            new ClosedFormFibonacciSolver,
#endif

#ifdef SUPPORTS_ITERATIVE
            new IterativeFibonacciSolver,
#endif
    };

    auto time = measureExecTime<microseconds>([&]() {
        (*solvers[0])(FIBONACCI_NUMBER);
    });
    std::cout << "Elapsed time: " << time << std::endl;

    for (uint32_t i = 1; i < sizeof(solvers) / sizeof(solvers[0]); i++) {
        FibonacciSolver &solver = *solvers[i];
        auto elapsed = measureExecTime<microseconds>([&]() {
            for (uint j = 1; j < TEST_ITERATIONS; j++) {
                solver(FIBONACCI_NUMBER);
            }
        });
        std::cout << "Elapsed time: " << elapsed << std::endl;
    }
    return 0;
}

template <typename T>
uint64_t measureExecTime(const std::function<void(void)> &measured) {
    system_clock::time_point start = system_clock::now();
    measured();
    system_clock::time_point stop = system_clock::now();
    T elapsed = duration_cast<T>(stop - start);
    return elapsed.count();
}