#include "BenchmarkSuite.h"

BenchmarkSuite::BenchmarkSuite(double sampleRate) 

    : sampleRate_(sampleRate) 
{}

std::vector<double> BenchmarkSuite::generateSignal(std::size_t N) 
{
    SignalGenerator gen(sampleRate_, N);  

    gen.addSineWave(50.0, 1.0);
    gen.addSineWave(120.0, 0.5);
    gen.addSineWave(200.0, 0.3);

    return gen.generateSignal();
}

// Loops over N sizes (256 --> 8192)
// Calls FFT/DFT via BenchmarkRunner
// Collects results
// stores vector of results
// Returns vector of results
std::vector<BenchmarkResult> BenchmarkSuite::runAll()
{
    std::vector<BenchmarkResult> results;

    BenchmarkRunner bench;

    for (auto N : testSizes_)
    {
        auto signal = generateSignal(N);
        FFTProcessor fft(sampleRate_, N);

        BenchmarkResult result;
        result.sampleSize = N;

        // warm up (DFT and FFT)
        for (int i = 0; i < 10; i++) 
        {
            fft.computeMagnitudeDFT(signal);
            fft.computeMagnitudeFFT(signal);
        }

        // DFT Benchmark
        result.dftTimeMs = bench.timeAverage([&fft, &signal]() {
            return fft.computeMagnitudeDFT(signal);
        }, 100);
        
        // FFT Benchmark
        result.fftTimeMs = bench.timeAverage([&fft, &signal]() {
            return fft.computeMagnitudeFFT(signal);
        }, 100);
        

        results.push_back(result);
    }
    return results;
}