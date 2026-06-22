#pragma once
#include <vector>

class SignalGenerator {
public:
    SignalGenerator(double sampleRate, double duration);

    std::vector<double> generateSignal();

    void addSineWave(double frequency, double amplitude);
    void setNoiseAmplitude(double amplitude);

private:
    double sampleRate;
    double duration;
    int numSamples;

    struct SineComponent {
        double frequency;
        double amplitude;
    };

    std::vector<SineComponent> components;
    double noiseAmplitude;

    double generateNoise();
};
