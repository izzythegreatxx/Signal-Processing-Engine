#pragma once


#include <vector>


class FIRFilter {
public:
    FIRFilter(const std::vector<double>& coefficients);

    std::vector<double> apply(const std::vector<double>& signal);

private:
std::vector<double> h_; // filter coefficients
};