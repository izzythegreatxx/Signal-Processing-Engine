#pragma once

#include "BenchmarkRunner.h"
#include <vector>
#include <fstream>
#include <stdexcept>

class CSVExporter {
public:

    static void exportSignal(const std::string& filename, 
                            const std::vector<double>& signal,
                            double sampleRate); 

    static void exportSpectrum(const std::string& filename, 
                               const std::vector<double>& magnitudes,
                               double sampleRate, 
                               std::size_t fftSize);
                    
    static void exportPeaks(const std::string& filename,
                            const std::vector<std::pair<int, double>>& peaks,
                            double sampleRate,
                            std::size_t fftSize);

    static void exportBenchmarkResults(const std::string& filename,
                                       const std::vector<BenchmarkResult>& results);    

private:
        static std::ofstream openFile(const std::string& filename);

};