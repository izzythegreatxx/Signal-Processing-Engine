#pragma once

#include <vector>
#include <string>

class Plotter {
public:
    void plotTimeDomain(const std::vector<double>& signal, double sampleRate,
                    size_t fftSize,const std::string& filename);

    void plotSpectrum(const std::vector<double>& magnitudes, double sampleRate,
                      size_t fftSize, const std::string& filename);
};

