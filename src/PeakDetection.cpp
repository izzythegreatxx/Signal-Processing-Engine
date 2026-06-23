#include "PeakDetection.h"





std::vector<std::pair<int, double>> PeakDetection::detectPeaks(
    const std::vector<double>& magnitudes, 
    double threshold) 
{
    std::vector<std::pair<int, double>> peaks;

    if (magnitudes.size() < 3) {
        return peaks; // Not enough data to detect peaks
    }

    for (std::size_t i = 1; i < magnitudes.size() -1; i++) {

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
