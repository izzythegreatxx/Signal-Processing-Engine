
#include <iostream>
#include "SignalGenerator.h"
#include "FFTProcessor.h"
#include "PeakDetection.h"
#include "CSVExporter.h"
#include "BenchmarkRunner.h"
#include "BenchmarkSuite.h"
#include "FIRFilter.h"
#include <vector>

// Function to create a simple moving average FIR filter
std::vector<double> createMovingAverageFilter(int size) {
    std::vector<double> h(size, 1.0 / size);
    return h;
}

int main() {
    double sampleRate = 1024.0; 
    size_t numSamples = 1024; // Number of samples in the signal

    // Create a SignalGenerator instance
    SignalGenerator gen(sampleRate, numSamples); // Sample rate: 1024 Hz, 1024 samples
    
    // Create a BenchmarkSuite instance
    BenchmarkSuite suite(sampleRate);

    // Run the benchmark suite and export results to CSV
    auto results = suite.runAll();
    CSVExporter::exportBenchmarkResults("plots/benchmark_results.csv", results);


    // Simulated RF signals
    gen.addSineWave(50.0, 1.0);  // 50 Hz sine wave with amplitude 1.0
    gen.addSineWave(120.0, 0.5); // 120 Hz sine wave with amplitude 0.5
    gen.addSineWave(200.0, 0.6); // 200 Hz sine wave with amplitude 0.6
    // Set noise amplitude
    gen.setNoiseAmplitude(0.1);
     
    // Generate the signal
    std::vector<double> signal = gen.generateSignal();

    auto raw = signal; // Store the raw signal for later export

    // Filter coefficients for a simple low-pass FIR filter
    auto coeffs = createMovingAverageFilter(10); // 10-point moving average filter
    FIRFilter filter(coeffs);
    auto filteredSignal = filter.apply(signal);
    
    size_t N = filteredSignal.size();
    
    // Create an FFTProcessor instance with the same sample rate
    FFTProcessor fft(sampleRate, N); // sample rate: 1kHz
    std::vector<double> filteredSpectrum = fft.computeMagnitudeFFT(filteredSignal);


    // Create an FFTProcessor instance with raw.size() as the FFT size
    FFTProcessor fft2(sampleRate, raw.size()); // sample rate: 1kHz
    std::vector<double> rawSpectrum = fft2.computeMagnitudeFFT(raw);


    // Detect peaks in the magnitude spectrum
    PeakDetection peakDetector;
    auto peaks = peakDetector.detectPeaks(filteredSpectrum, 0.1); // Threshold for peak detection

    for (auto& p : peaks) {
        int bin = p.first;
        double mag = p.second;

        double freq = fft2.binToFrequency(bin);

        std::cout << "Peak detected: " << freq << " Hz (mag=" << mag << ")\n";
    }

    // Export the filtered spectrum to a CSV file
    CSVExporter::exportSpectrum("plots/magnitude_spectrum.csv", filteredSpectrum, sampleRate, filteredSignal.size());

    // Export the raw spectrum to a CSV file
    CSVExporter::exportSpectrum("plots/raw_magnitude_spectrum.csv", rawSpectrum, sampleRate, raw.size());

    // Export the detected peaks to a CSV file
    CSVExporter::exportPeaks("plots/detected_peaks.csv", peaks, sampleRate, raw.size());

    // Export the time-domain signal to a CSV file
    CSVExporter::exportSignal("plots/time_domain_signal.csv", filteredSignal, sampleRate);  
}


