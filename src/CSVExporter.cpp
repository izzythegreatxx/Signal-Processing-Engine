#include "CSVExporter.h"
#include <iostream>


// Helper function to open a file and handle errors
std::ofstream CSVExporter::openFile(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    return file;
}

void CSVExporter::exportSignal(const std::string& filename,
                            const std::vector<double>& signal,
                            double sampleRate)
{
    std::ofstream file = openFile(filename);
    file << "Time (s), Amplitude\n";
    for (std::size_t i = 0; i < signal.size(); ++i) {
        file << (static_cast<double>(i) / sampleRate) << "," << signal[i] << "\n";
    }

}


void CSVExporter::exportSpectrum(const std::string& filename,
                               const std::vector<double>& magnitudes,
                               double sampleRate,
                               std::size_t fftSize)
{
    std::ofstream file = openFile(filename);    
    file << "Frequency (Hz),Magnitude\n";
    for (std::size_t i = 0; i < magnitudes.size(); ++i) {
        double frequency = (static_cast<double>(i) * sampleRate) / fftSize;
        file << frequency << "," << magnitudes[i] << "\n";
    }

}


void CSVExporter::exportPeaks(const std::string& filename,
                            const std::vector<std::pair<int, double>>& peaks,
                            double sampleRate,
                            std::size_t fftSize)
{
    std::ofstream file = openFile(filename);
    file << "Frequency (Hz),Magnitude\n";
    for (const auto& peak : peaks) {
        double frequency = (static_cast<double>(peak.first) * sampleRate) / fftSize;
        file << frequency << "," << peak.second << "\n";
    }

}