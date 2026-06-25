#pragma once 

#include <vector>
#include "BenchmarkRunner.h"
#include "FFTProcessor.h"
#include "SignalGenerator.h"


class BenchmarkSuite {
public:
    BenchmarkSuite(double sampleRate);
    std::vector<BenchmarkResult> runAll();

private:
    double sampleRate_;
    std::vector<double> generateSignal(std::size_t N);

    std::vector<std::size_t> testSizes_ = { 256, 512, 1024, 2048, 4096, 8192 }; 
};