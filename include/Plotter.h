#pragma once

#include <vector>
#include <string>

class Plotter {
public:
    void plotTimeDomain(const std::vector<double>& signal, double sampleRate,
                    size_t fftSize,const std::string& filename);

    void plotSpectrum(const std::vector<double>& magnitudes, double sampleRate,
                      size_t fftSize, const std::string& filename);
    
    void plotBenchmarkResults(const std::vector<std::size_t>& N,
                              const std::vector<double>& dftTimes,
                              const std::vector<double>& fftTimes, 
                              const std::vector<double>& speedup,
                              const std::string& filename);
};

