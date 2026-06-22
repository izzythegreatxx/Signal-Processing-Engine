#pragma once
#include <vector>
#include <utility>
#include <cstddef>

class FFTProcessor {
public:
    FFTProcessor(double sampleRate, size_t fftSize); 
    // Computes the magnitude of the FFT for a given signal
    std::vector<double> computeMagnitude(const std::vector<double>& signal); 
    // Detects peaks in the magnitude spectrum above a specified threshold
    std::vector<std::pair<int, double>> detectPeaks(
        const std::vector<double>& magnitudes, 
        double threshold);
    // Converts a bin index to its corresponding frequency
    double binToFrequency(int bin) const;

private:
    double sampleRate_;
    size_t N_;
    
    std::vector<double> window_;

    std::vector<double> createHannWindow() const;
    void applyWindow(std::vector<double>& signal) const;


};