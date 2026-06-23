
#include <iostream>
#include "SignalGenerator.h"
#include "FFTProcessor.h"
#include "Plotter.h"
#include "PeakDetection.h"

int main() {
    double sampleRate = 1024.0; 
    double duration = 1.0; // 1 second

    // Create a SignalGenerator instance with a sample rate of 1000 Hz and a duration of 1 second
    SignalGenerator gen(sampleRate, duration); // Sample rate: 1kHz, Duration: 1 second

    // Create a Plotter instance
    Plotter plotter;

    // Simulated RF signals
    gen.addSineWave(50.0, 1.0);  // 50 Hz sine wave with amplitude 1.0
    gen.addSineWave(120.0, 0.5); // 120 Hz sine wave with amplitude 0.5
    gen.addSineWave(200.0, 0.3); // 200 Hz sine wave with amplitude 0.3

    gen.setNoiseAmplitude(0.2); // Set noise amplitude

    std::vector<double> signal = gen.generateSignal();

    plotter.plotTimeDomain(signal, sampleRate, signal.size(), "plots/signal.png");

    
    // Create an FFTProcessor instance with the same sample rate
    FFTProcessor fft(sampleRate, signal.size()); // sample rate: 1kHz
    std::vector<double> magnitudes = fft.computeMagnitudeFFT(signal);
    std::cout << "DFT Magnitudes:" << std::endl;
    for (size_t i = 0; i < 100; i++) { 
        double freq = fft.binToFrequency(i);
        std::cout << "Bin " << i << " (" << freq << " Hz): " << magnitudes[i] <<std::endl;
    }

    plotter.plotSpectrum(magnitudes, sampleRate, signal.size(), "plots/spectrum.png");


    PeakDetection peakDetector;
    auto peaks = peakDetector.detectPeaks(magnitudes, 0.1); // Threshold for peak detection

    for (auto& p : peaks) {
        int bin = p.first;
        double mag = p.second;

        double freq = fft.binToFrequency(bin);

        std::cout << "Peak detected: " << freq << " Hz (mag=" << mag << ")\n";
    }
 

    return 0;
}