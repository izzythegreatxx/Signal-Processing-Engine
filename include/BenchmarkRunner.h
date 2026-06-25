#pragma once

#include <chrono>
#include <utility>


struct BenchmarkResult {
    std::size_t sampleSize;
    double dftTimeMs;
    double fftTimeMs;
    double speedup;

};

class BenchmarkRunner {
public:
    template<typename Func>
    double timeAverage(Func&& f, int runs) 

    {
        double total = 0.0;

        for (int i = 0; i < runs; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            std::forward<Func>(f)(); 
            auto end = std::chrono::high_resolution_clock::now();
            
            total += std::chrono::duration<double, std::milli>(end - start).count();
        }

        return total / runs;
    }
}; 

     