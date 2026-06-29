#include "FIRFilter.h"

FIRFilter::FIRFilter(const std::vector<double>& coefficients)
    : h_(coefficients) {}

std::vector<double> FIRFilter::apply(const std::vector<double>& signal) {
    int N = signal.size();
    int M = h_.size();

    std::vector<double> output(N, 0.0);

    for (int n = 0; n < N; n++) {
        double sum = 0.0;
        for (int k = 0; k < M; k++) {
            if ( n - k >= 0 ) {
                sum += h_[k] * signal[n - k];
            }
        }
        output[n] = sum;
    }
    return output;
}