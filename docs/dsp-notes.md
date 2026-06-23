# Digital Signal Processing (DSP) Notes

## What is Digital Signal Processing?

Digital Signal Processing (DSP) is the analysis and manipulation of signals after they have been converted into digital data.

A signal is any measurable quantity that changes over time or space.

Examples include:

* Audio from a microphone
* Radio frequency (RF) signals
* Radar returns
* Sonar echoes
* Medical ultrasound
* Accelerometer measurements
* Temperature sensors
* Satellite communications

The goal of DSP is to extract useful information from sampled data.

---

# Analog vs. Digital Signals

## Analog Signal

A continuous waveform.

Examples:

* Human speech
* Radio waves
* Electrical voltage
* Sound pressure

An analog signal can have infinitely many values between two points in time.

---

## Digital Signal

A digital signal consists of discrete samples taken at regular time intervals.

Example:

```text
Time (s)      Amplitude
0.000         0.32
0.001         0.85
0.002         1.21
0.003         0.94
```

These samples are stored in software as a vector.

```cpp
std::vector<double> samples;
```

---

# Sampling

Sampling converts a continuous analog signal into discrete digital samples.

The number of samples collected each second is called the **sampling rate**.

Example:

```text
1024 samples/second
```

This means the ADC measures the signal 1024 times every second.

---

# Time Domain

The time domain shows how signal amplitude changes over time.

Example:

```text
Amplitude

 ^
 |        /\
 |       /  \
 |______/____\_______ Time
```

The SignalGenerator in this project produces time-domain data.

---

# Frequency Domain

The frequency domain shows which frequencies exist in a signal.

Example:

```text
Magnitude

 ^
 |         *
 |         *
 |    *    *
 |____|____|__________
     50   120   200 Hz
```

Instead of looking at amplitude over time, we look at the energy present at each frequency.

---

# Fourier Transform

The Fourier Transform converts a signal from:

```text
Time Domain
      ↓
Frequency Domain
```

The transform determines how much of each sinusoidal frequency exists inside the signal.

---

# Discrete Fourier Transform (DFT)

The DFT computes every frequency individually.

## Time Complexity

```text
O(N²)
```

### Advantages

* Easy to understand
* Exact mathematical solution

### Disadvantages

* Slow for large datasets

---

# Fast Fourier Transform (FFT)

The FFT produces the same result as the DFT while dramatically reducing computation time.

## Time Complexity

```text
O(N log N)
```

The FFT is one of the most important algorithms in engineering because it enables real-time signal processing.

---

# Correlation

The FFT does not "look for" frequencies.

Instead, it measures how strongly the sampled signal correlates with sinusoidal basis functions.

A strong correlation produces a large magnitude at that frequency.

---

# Window Functions

Window functions reduce discontinuities at the beginning and end of a sampled signal.

Current implementation:

* Hann Window

Benefits:

* Reduces spectral leakage
* Produces cleaner frequency spectra

Common window functions:

* Hann
* Hamming
* Blackman
* Rectangular

---

# Spectral Leakage

When a signal does not contain an integer number of cycles within the sampling window, energy spreads into neighboring frequency bins.

This phenomenon is called **spectral leakage**.

Window functions reduce this effect.

---

# Noise

Real-world signals always contain noise.

Sources include:

* Electrical interference
* Sensor imperfections
* Thermal noise
* Quantization noise
* Environmental interference

One goal of DSP is to separate useful signals from noise.

---

# Peak Detection

After computing the frequency spectrum, peak detection identifies dominant frequency components.

Typical applications include:

* Audio pitch detection
* Radar target detection
* RF signal identification
* Fault detection
* Vibration analysis

---

# Typical DSP Pipeline

```text
Physical Signal
       │
       ▼
Sensor / Antenna / Microphone
       │
       ▼
ADC
       │
       ▼
Digital Samples
       │
       ▼
Windowing
       │
       ▼
FFT
       │
       ▼
Magnitude Spectrum
       │
       ▼
Filtering
       │
       ▼
Peak Detection
       │
       ▼
Feature Extraction
       │
       ▼
Classification / Decision
```

---

# Applications of DSP

* Radar
* Sonar
* RF Communications
* Audio Processing
* Speech Recognition
* Medical Imaging
* Wireless Networks
* Satellite Communications
* Image Processing
* Vibration Analysis
* Autonomous Vehicles

---

# Personal Notes

## Major Realizations

* Sampled signals contain amplitudes over time, not frequencies.
* Frequencies are inferred using the Fourier Transform.
* The SignalGenerator simulates a real sensor.
* Any real sensor (microphone, ADC, SDR) can replace the SignalGenerator without changing the FFT algorithm.
* FFT is a faster implementation of the DFT, not a different mathematical transform.

---

# Topics to Learn Next

* Nyquist-Shannon Sampling Theorem
* FIR Filters
* IIR Filters
* Digital Convolution
* Cross-Correlation
* Autocorrelation
* Power Spectral Density (PSD)
* Spectrograms (Short-Time FFT)
* Complex Numbers in DSP
* IQ Signals
* Radar Signal Processing
* Digital Communications
* Adaptive Filtering
* Kalman Filters
