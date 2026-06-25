#include "CSVExporter.h"
#include "BenchmarkRunner.h"
#include <fstream>
#include <iostream>


// Helper function to open a file and handle errors
std::ofstream CSVExporter::openFile(const std::string& filename)
{   // Create an output file stream
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    return file;
}
// Export signal data to CSV
void CSVExporter::exportSignal(const std::string& filename,
                            const std::vector<double>& signal,
                            double sampleRate)
{
    std::ofstream file = openFile(filename);

    // CSV Header
    file << "Time (s), Amplitude\n";

    for (std::size_t i = 0; i < signal.size(); ++i) {
        file << (static_cast<double>(i) / sampleRate) << "," << signal[i] << "\n";
    }

}

// Export spectrum data to CSV
void CSVExporter::exportSpectrum(const std::string& filename,
                               const std::vector<double>& magnitudes,
                               double sampleRate,
                               std::size_t fftSize)
{
    std::ofstream file = openFile(filename);   
    
    // CSV Header
    file << "Frequency (Hz),Magnitude\n";

    for (std::size_t i = 0; i < magnitudes.size(); ++i) {
        double frequency = (static_cast<double>(i) * sampleRate) / fftSize;
        file << frequency << "," << magnitudes[i] << "\n";
    }

}

// Export detected peaks to CSV
void CSVExporter::exportPeaks(const std::string& filename,
                            const std::vector<std::pair<int, double>>& peaks,
                            double sampleRate,
                            std::size_t fftSize)
{
    std::ofstream file = openFile(filename);
    // CSV Header
    file << "Frequency (Hz),Magnitude\n";

    for (const auto& peak : peaks) {
        double frequency = (static_cast<double>(peak.first) * sampleRate) / fftSize;
        file << frequency << "," << peak.second << "\n";
    }

}

// Export benchmark results to CSV
void CSVExporter::exportBenchmarkResults(const std::string& filename,
                                       const std::vector<BenchmarkResult>& results)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open benchmark CSV file: " + filename);
    } 
    
    // CSV Header
    file << "Sample_Size,DFT_Time (ms),FFT_Time (ms),Speedup\n";

    for (const auto& result : results) {
        // Calculate speedup, ensuring no division by zero
        double speedup = (result.fftTimeMs > 0.0) ?
        (result.dftTimeMs / result.fftTimeMs) : 0.0;
        // Write the benchmark results to the CSV file
        file << result.sampleSize << "," 
            << result.dftTimeMs << "," 
            << result.fftTimeMs << "," 
            << speedup << "\n";
    }    
}