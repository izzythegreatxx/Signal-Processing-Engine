#pragma once

#include <vector>
#include <utility>
#include <cstddef>


class PeakDetection {
public:

    // Detects peaks in the magnitude spectrum above a specified threshold
    std::vector<std::pair<int, double>>detectPeaks(
        const std::vector<double>& magnitudes, 
        double threshold);

    };