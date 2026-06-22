#include <stdexcept>
#include "FFTProcessor.h"
#include <cmath>
#include <vector>

static constexpr double PI = 3.14159265358979323846;

std::vector<double> FFTProcessor::createHannWindow() const {
    std::vector<double> window(N_);

    for (size_t n = 0; n < N_; n++) {
        window[n] = 0.5 * (1.0 - std::cos(2.0 * PI * n / (N_ -1)));
    }
    return window;
}

void FFTProcessor::applyWindow(std::vector<double>& signal) const {
    for (size_t i = 0; i < signal.size(); i++) {
        signal[i] *= window_[i];    
    }
}

FFTProcessor::FFTProcessor(double sampleRate, size_t fftSize)
    : sampleRate_(sampleRate), N_(fftSize) 
    {
        window_ = createHannWindow();
    }

std::vector<std::pair<int, double>> FFTProcessor::detectPeaks(
    const std::vector<double>& magnitudes, 
    double threshold) 
{
    std::vector<std::pair<int, double>> peaks;

    if (magnitudes.size() < 3) {
        return peaks; // Not enough data to detect peaks
    }

    for (size_t i = 1; i < magnitudes.size() -1; i++) {

        double prev = magnitudes[i -1];
        double curr = magnitudes[i];
        double next = magnitudes[i + 1];

        // local maximum + above threshold
        if (curr > prev && curr > next && curr > threshold) {
            peaks.push_back({static_cast<int>(i), curr});
        }
    }
    return peaks;  
}

double FFTProcessor::binToFrequency(int bin) const {
    return bin * (sampleRate_ / N_);
}

 
std::vector<double> FFTProcessor::computeMagnitude(const std::vector<double>& signal) {
    if (signal.size() != N_) {
        throw std::runtime_error("Input signal size must match FFT size");
    }
    
    std::vector<double> samples= signal;

    applyWindow(samples);

    double windowSum = 0.0;
    for (double w : window_) {
        windowSum += w;
    }

    // DFT computation
    int N = samples.size();
    std::vector<double> magnitudes(N / 2, 0.0); // Only need the first N/2 bins for magnitude 

    // outer loop determines how much of the signal is in each frequency bin
    for (int k = 0; k < N / 2; k++) {
        double real = 0.0;
        double imag = 0.0;

        // inner loop computes the contribution of each time-domain sample to the k-th frequency bin
        for (int n = 0; n < N; n++) {
        
            // k = frequency being tested, n = time-domain, N = total samples
            double angle = 2.0 * PI * k * n / N;
            // DFT formula: X[k] = sum_{n=0}^{N-1} x[n] * e^{-j*2*pi*k*n/N}
            real += samples[n] * cos(angle);
            imag -= samples[n] * sin(angle);

        }
        // Magnitude is sqrt(real^2 + imag^2)
        magnitudes[k] = (2.0 / windowSum) * sqrt(real * real + imag * imag); 
    }

    return magnitudes;
}

