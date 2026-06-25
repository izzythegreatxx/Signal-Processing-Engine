#pragma once
#include <vector>
#include <cstddef>

class SignalGenerator {
public:
    SignalGenerator(double sampleRate, std::size_t numSamples);

    std::vector<double> generateSignal();

    void addSineWave(double frequency, double amplitude);
    void setNoiseAmplitude(double amplitude);

private:
    double sampleRate;
    double duration;
    std::size_t numSamples;

    struct SineComponent {
        double frequency;
        double amplitude;
    };

    std::vector<SineComponent> components;
    double noiseAmplitude;

    double generateNoise();
};
