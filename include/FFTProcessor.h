#pragma once
#include <vector>
#include <utility>
#include <cstddef>
#include <complex>

class FFTProcessor {
public:
    FFTProcessor(double sampleRate, size_t fftSize); 
    // Computes the magnitude of the DFT for a given signal
    std::vector<double> computeMagnitudeDFT(const std::vector<double>& signal);

    // Computes the magnitude of the FFT for a given signal
    std::vector<double> computeMagnitudeFFT(const std::vector<double>& signal);


    // Detects peaks in the magnitude spectrum above a specified threshold
    std::vector<std::pair<int, double>> detectPeaks(
        const std::vector<double>& magnitudes, 
        double threshold);
    // Converts a bin index to its corresponding frequency
    double binToFrequency(int bin) const;

private:
    // Sample rate of the signal
    double sampleRate_;
    
    // Size of the FFT (number of samples)
    size_t N_;
    
    // Hann window coefficients
    std::vector<double> window_;

    // Creates a Hann window of size N_
    std::vector<double> createHannWindow() const;
    void applyWindow(std::vector<double>& signal) const;

    // Cooley - Tukey FFT algorithm implementation
    void fft(std::vector<std::complex<double>>& data) const;

    // Checks if a number is a power of two (required for FFT) 1024, 2048, etc.
    bool isPowerOfTwo(size_t n) const;


};