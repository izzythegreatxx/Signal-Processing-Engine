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

    plt::title("Frequency Spectrum");
    plt::xlabel("Frequency (Hz)");
    plt::ylabel("Magnitude");
    plt::grid(true);

    plt::save(filename);
    plt::close();
 }