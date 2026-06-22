#include "SignalGenerator.h"
#include <cmath>
#include <random>

/*
This implementation of the SignalGenerator class allows you to create a signal 
composed of multiple sine waves and additive noise. You can specify the sample rate, 
duration, and the parameters of each sine wave (frequency and amplitude). 
The generateSignal() method will produce the final signal as a vector of doubles, 
which can be used for further processing or analysis.
*/

static constexpr double PI = 3.14159265358979323846;

SignalGenerator::SignalGenerator(double sampleRate, double duration)
    : sampleRate(sampleRate), duration(duration), noiseAmplitude(0.0)
{
    numSamples = static_cast<int>(sampleRate * duration);
}
// Adds a sine wave component to the signal with the specified frequency and amplitude
void SignalGenerator::addSineWave(double frequency, double amplitude) {
    components.push_back({frequency, amplitude});
}

void SignalGenerator::setNoiseAmplitude(double amplitude) {
    noiseAmplitude = amplitude;
}

double SignalGenerator::generateNoise() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<double> dist(0.0, 1.0);

    return noiseAmplitude * dist(gen);
}
// Generates the final signal by summing all sine wave components and adding noise
std::vector<double> SignalGenerator::generateSignal() {
    std::vector<double> signal;
    signal.reserve(numSamples);
    
    for (int n = 0; n < numSamples; n++) {

        double t = n / sampleRate; // Time in seconds for the current sample
        double value = 0.0; 

        // Sum all sine wave components
        for (const auto& comp : components) {
            // Add the contribution of each sine wave component to the signal value
            value += comp.amplitude * std::sin(2.0 * PI * comp.frequency * t);

        }

        // Add noise
        value += generateNoise();

        signal.push_back(value);
    }
    return signal;
}