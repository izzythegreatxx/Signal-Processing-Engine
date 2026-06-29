#include <stdexcept>
#include "FFTProcessor.h"
#include <cmath>
#include <vector>
#include <complex>
#include <iostream>

static constexpr double PI = 3.14159265358979323846;


bool FFTProcessor::isPowerOfTwo(size_t n) const {
    return n > 0 && (n & (n - 1)) == 0;
}


void FFTProcessor::fft(std::vector<std::complex<double>>& data) const {
    const size_t N = data.size();

    if (N <= 1) {
        return;
    }

    std::vector<std::complex<double>> even(N / 2);
    std::vector<std::complex<double>> odd(N / 2);

    for (size_t i = 0; i < N / 2; i++) {
        even[i] = data[2 * i];
        odd[i] = data[2 * i + 1];
    } 
    // Recursively apply FFT to even and odd indexed elements
    fft(even);
    fft(odd);

    for (size_t k = 0; k < N / 2; k++) {
        std::complex<double> twiddle = std::polar(1.0, -2.0 * PI * k / N) * odd[k];

        data[k] = even[k] + twiddle;
        data[k + N / 2] = even[k] - twiddle;
    }
}

// FFT implementation based on Cooley-Tukey algorithm

std::vector<double> FFTProcessor::computeMagnitudeFFT(const std::vector<double>& signal) {
    if (signal.size() != N_) {
        throw std::runtime_error("Signal size must match FFT size");
    }

    if (!isPowerOfTwo(N_)) {
        throw std::runtime_error("FFT size must be a power of two");
    }

    std::vector<double> samples = signal;
    applyWindow(samples);

    double coherentGain = 0.0;
    for (double w : window_) {
        coherentGain += w;
    }
    coherentGain /= N_; // Normalize coherent gain

    std::vector<std::complex<double>> data(N_);

    for (size_t i = 0; i < N_; i++) {
        // Convert real samples to complex numbers (imaginary part is 0)
        data[i] = std::complex<double>(samples[i], 0.00);
    }

    // Perform FFT on the complex data
    fft(data);

    // Compute the magnitude of the FFT results
    std::vector<double> magnitudes(N_ / 2);

    for (size_t k = 0; k < N_ / 2; k++) {
        // Normalize by window sum and scale for single-sided spectrum
        magnitudes[k] = (2.0 / coherentGain) * std::abs(data[k]) / N_; // Normalize by N_ to get the correct amplitude
    }

    return magnitudes;
}

std::vector<double> FFTProcessor::createHannWindow() const {
    std::vector<double> window(N_);

    for (size_t n = 0; n < N_; n++) {
        window[n] = 0.5 * (1.0 - std::cos(2.0 * PI * n / (N_ -1)));
    }
    return window;
}

void FFTProcessor::applyWindow(std::vector<double>& signal) const {
    size_t limit = std::min(signal.size(), window_.size());
    for (size_t i = 0; i < limit; i++) {
        signal[i] *= window_[i];    
    }
}

FFTProcessor::FFTProcessor(double sampleRate, size_t fftSize)
    : sampleRate_(sampleRate), N_(fftSize) 
    {
        window_ = createHannWindow();
    }

double FFTProcessor::binToFrequency(int bin) const {
    return bin * (sampleRate_ / N_);
}

 
std::vector<double> FFTProcessor::computeMagnitudeDFT(const std::vector<double>& signal) {
    if (signal.size() != N_) {
        throw std::runtime_error("Input signal size must match FFT size");
    }
    
    std::vector<double> samples= signal;

    applyWindow(samples);

    double coherentGain = 0.0;
    for (double w : window_) {
        coherentGain += w;
    }
    coherentGain /= N_; // Normalize coherent gain

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
        // amplitude scaling: multiply by 2 for single-sided spectrum and divide by coherent gain to account for windowing
        magnitudes[k] = (2.0 / coherentGain) * sqrt(real * real + imag * imag) / N_; // Normalize by N_ to get the correct amplitude
    }
    return magnitudes;
}

