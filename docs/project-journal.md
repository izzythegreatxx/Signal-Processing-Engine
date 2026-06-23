# Signal Processing Engine - Project Journal

## June 18–23, 2026

### Project Goal

Build a modular C++ signal processing framework to strengthen my understanding of Digital Signal Processing (DSP) and prepare for software engineering roles involving RF, radar, and EO/IR systems.

The long-term objective is to replace simulated signals with real sensor data from hardware such as microphones, ADCs, Raspberry Pi peripherals, or software-defined radios (RTL-SDR).

---

## Initial Questions

Before writing any code, I wanted to understand:

- What is an FFT?
- How can a computer determine frequencies from only time samples?
- What does a sampled signal actually represent?
- Why is FFT used in radar and signal processing?

Initially, I assumed FFT somehow "looked" at the signal and directly detected frequencies.

After studying the mathematics and implementing the algorithm myself, I learned that FFT measures how strongly sampled data correlates with sinusoidal basis functions of different frequencies.

---

## Major Realizations

One of the biggest breakthroughs was understanding that sampled signals **do not contain frequencies directly.**

A sampled signal contains only amplitudes measured over time.

The frequencies are hidden inside those changing amplitudes.

The FFT attempts to recover those frequencies.

---

## Simulation vs. Real Hardware

Another important realization was understanding the purpose of the `SignalGenerator`.

The `SignalGenerator` is **not** part of the FFT.

It simply simulates a real sensor.

Eventually it can be replaced with:

- USB microphone
- ADC
- Raspberry Pi sensor
- RTL-SDR
- Recorded RF data

The FFT algorithm itself never changes because every sensor ultimately provides the same interface:

```cpp
std::vector<double> samples;
```

---

## Project Milestones

### Completed

- Built the `SignalGenerator`
- Implemented a naive DFT
- Added a Hann window
- Implemented peak detection
- Added plotting of the time-domain signal
- Added plotting of the frequency spectrum
- Refactored the project into `src/` and `include/`
- Added a Makefile
- Began implementing a recursive FFT

---

## Next Steps

- Complete the recursive FFT implementation
- Compare DFT vs. FFT execution time
- Implement FIR filters
- Implement IIR filters
- Export CSV data
- Add real microphone input
- Integrate Raspberry Pi sensors
- Add RTL-SDR support
- Implement signal classification experiments



# June 23, 2026

## Project Changes

- Renamed computeMagnitude() to computeMagnitudeDFT()
- Implemented recursive Cooley-Tukey FFT
- Switched sample size from 1000 to 1024
- Added power-of-two validation

### What I learned

- A DFT computes every frequency bin individually.
- FFT produces the same frequency spectrum using a divide-and-conquer algorithm.
- FFT requires the sample size to be a power of two.
- The FFT implementation recovered the same dominant peaks (50Hz, 120Hz, 200Hz) as the DFT.
- Minor differences in the noise floor are expected due to normalization, sample count, and random noise.

### Questions

- Why does normalization affect peak amplitude?
- Compare Hann vs Hamming window.
