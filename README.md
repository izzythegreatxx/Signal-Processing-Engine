# Signal Processing Engine (C++ FFT-Based RF Analysis System)

## Overview

The Signal Processing Engine is a modular C++ framework for simulating, analyzing, and processing noisy RF-like signals. It implements a full signal pipeline including signal generation, FFT-based spectral analysis, filtering, and frequency-domain feature detection.

The system is designed to emulate real-world signal processing workflows used in RF analysis, radar-like systems, and embedded sensor data interpretation.

---

## Key Features

- Synthetic RF signal generation with configurable noise and interference
- Time-domain signal processing pipeline
- FFT-based frequency spectrum analysis
- Frequency-domain filtering (band-pass / threshold-based filtering)
- Peak detection for identifying dominant frequency components
- Signal-to-noise separation and analysis
- CSV export for downstream visualization and evaluation

---

## System Pipeline

The processing flow is structured as follows:

1. Signal Generation  
   - Simulates RF-like signals using sine waves and noise models

2. Preprocessing  
   - Optional windowing (e.g., Hamming window) to reduce spectral leakage

3. FFT Processing  
   - Converts time-domain signals into frequency-domain representation

4. Spectrum Analysis  
   - Computes magnitude spectrum and identifies frequency components

5. Detection & Filtering  
   - Applies thresholds and band filtering to isolate meaningful signals

6. Output Generation  
   - Exports results to CSV for visualization and analysis

---

## Example Use Case

- Detecting dominant frequency components in noisy RF environments
- Simulating radar-like signal returns
- Analyzing interference and noise behavior in frequency space
- Evaluating filtering effectiveness using SNR comparisons

---

## Output Data

The system generates structured CSV outputs:

- `time_domain.csv`  
  Raw signal samples over time

- `frequency_spectrum.csv`  
  FFT magnitude vs frequency

- `detections.csv`  
  Detected frequency peaks and signal candidates

---

## Tech Stack

- C++
- Standard Template Library (STL)
- (Optional) FFTW library for optimized FFT computation
- Linux (WSL / Ubuntu)
- CMake (optional build system)

---

## Why This Project Matters

This project demonstrates core competencies in:

- Digital signal processing (DSP)
- Frequency-domain analysis
- Noise modeling and filtering
- Algorithmic implementation in C++
- System-level software design

These concepts are directly applicable to RF systems, radar signal processing, and embedded sensor analysis environments.

---

## Future Improvements

- Real-time signal processing using streaming input
- GUI visualization of frequency spectrum
- Integration with Raspberry Pi sensor inputs
- Advanced detection algorithms (autocorrelation / adaptive filtering)
- Performance benchmarking and optimization

---

## Author

Built as a systems-level signal processing project focused on RF-style analysis and FFT-based feature extraction in C++.
