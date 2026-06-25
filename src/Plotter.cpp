#include "Plotter.h" 
#include "matplotlibcpp.h"

#include <vector>
#include <string>
namespace plt = matplotlibcpp;

void Plotter::plotTimeDomain(const std::vector<double>& signal, double sampleRate,
                        size_t fftSize, const std::string& filename) {

    std::vector<double> time(signal.size());

    for (size_t  i = 0; i < signal.size(); ++i) {
        time[i] = i / sampleRate;
    }

    plt::figure();
    plt::plot(time, signal);

    plt::title("Time-Domain Signal");
    plt::xlabel("Time (s)");
    plt::ylabel("Amplitude");
    plt::grid(true);

    plt::save(filename);
    plt::close();
  
 }

 void Plotter::plotSpectrum(const std::vector<double>& magnitudes, double sampleRate, 
                          size_t fftSize, const std::string& filename) {

    std::vector<double> frequencies(magnitudes.size());

    for (size_t i = 0; i < magnitudes.size(); ++i) {
        frequencies[i] = i * sampleRate / fftSize;;
    }

    plt::figure();
    plt::plot(frequencies, magnitudes);

    plt::title("FFT Magnitude Spectrum");
    plt::xlabel("Frequency (Hz)");
    plt::ylabel("Normalized Magnitude");
    plt::grid(true);

    plt::save(filename);
    plt::close();
 }

 void Plotter::plotBenchmarkResults(const std::vector<std::size_t>& N,
                                  const std::vector<double>& dftTimes,
                                  const std::vector<double>& fftTimes, 
                                  const std::vector<double>& speedup,
                                  const std::string& filename) {
    plt::figure(); 
    
    // Plot DFT and FFT times
    std::vector<double> x(N.begin(), N.end()); 

    // Plot 1: DFT vs FFT timing
    plt::figure();
    plt::plot(x, dftTimes, {{"label", "DFT (O(N^2))"}});
    plt::plot(x, fftTimes, {{"label", "FFT (O(N log N))"}});

    plt::xlabel("Sample Size (N)");
    plt::ylabel("Time (ms)");
    plt::title("DFT vs FFT Performance Scaling");
    plt::legend();
    plt::grid(true);

    plt::save(filename + "_timing.png");
    plt::close();

    // Plot Speedup 
    plt::figure();
    plt::plot(x, speedup);

    plt::xlabel("Sample Size (N)");
    plt::ylabel("Speedup (DFT / FFT)");
    plt::title("FFT Speedup vs DFT");
    plt::grid(true);

    plt::save(filename + "_speedup.png");
    plt::close();
    
}   