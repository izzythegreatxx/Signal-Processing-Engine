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



# June 24, 2026

## Benchmarking DFT vs FFT Performance

### Objective
Implement a performance benchmarking system to compare the execution time of DFT and FFT implementations using statistical averaging.

---

### What I Built

- Implemented a `BenchmarkRunner` class using `std::chrono`
- Added lambda-based timing system for reusable benchmarking
- Introduced averaging over multiple runs (100 iterations)
- Separated computation (FFTProcessor) from measurement (BenchmarkRunner)

---

### Key Results

For a sample signal:

- DFT Average Time: ~18.18 ms  
- FFT Average Time: ~0.86 ms  
- Observed Speedup: ~21× faster FFT performance

---

### Key Learnings

- DFT has O(N²) complexity and scales poorly with signal size
- FFT reduces complexity to O(N log N), resulting in major performance gains
- Averaging multiple runs improves measurement stability
- Benchmarking must isolate computation (no printing or extra I/O)

---

### Design Improvements

- Separated responsibilities:
  - FFTProcessor → signal processing
  - BenchmarkRunner → performance measurement
  - CSVExporter → data export

- Used lambda functions for generic benchmarking:
  - Allows benchmarking any callable function
  - Removes dependency between benchmarking and DSP code

---

### Next Steps

- Benchmark across multiple signal sizes (256 → 8192 samples)
- Export results to CSV for visualization
- Plot complexity curves (DFT vs FFT)
- Add warm-up runs for more accurate benchmarking

## June 25, 2026 — Benchmarking & Performance Analysis Upgrade

### Objective

Extend the DSP system to include formal performance benchmarking of DFT vs FFT implementations and analyze algorithmic complexity empirically.

---

### What I Implemented Today

#### Benchmarking System Completion
- Moved benchmarking responsibility fully into `BenchmarkSuite`
- Removed benchmarking logic from `main.cpp`
- Standardized experiment execution across multiple signal sizes:
  - 256 → 8192 samples

---

#### CSV Export System
- Implemented structured CSV export for benchmarking results
- Added support for:
  - DFT execution time
  - FFT execution time
  - Speedup calculation (DFT / FFT)

Output format:
Sample_size,DFT_Time_ms,FFT_Time_ms,Speedup


---

#### Speedup Metric Introduction

Defined and implemented:

Speedup = DFT_Time / FFT_Time


This metric provides a direct comparison between naive and optimized Fourier transform implementations.

---

### Key Results

Observed performance scaling:

- FFT speedup increases with input size
- At N = 8192:
  - DFT ≈ 1418 ms
  - FFT ≈ 7.2 ms
  - Speedup ≈ 195×

---

### Key Insights

#### 1. Algorithmic Complexity Verified
- DFT exhibits O(N²) scaling
- FFT exhibits O(N log N) scaling
- Empirical results match theoretical expectations

#### 2. Importance of Speedup Metric
- Raw execution times are difficult to compare across scales
- Speedup provides a normalized performance comparison
- Clearly shows FFT advantage increasing with N

#### 3. Benchmarking Stability Improvements
- Introduced warm-up runs (to reduce cache effects)
- Averaged multiple runs for stability
- Isolated computation from I/O and printing

---

### Design Improvements

- Clean separation of responsibilities:
  - BenchmarkSuite → experiment orchestration
  - BenchmarkRunner → timing utility
  - CSVExporter → data serialization
  - FFTProcessor → signal processing core

---

### Real-World Relevance

This benchmarking structure mirrors real DSP validation workflows used in:

- Radar signal processing systems
- RF spectrum analysis pipelines
- Embedded sensor performance testing
- EO/IR signal processing evaluation

---

### Next Steps

- Generate visualization of benchmark curves
- Plot:
  - DFT vs FFT execution time
  - Speedup vs N
- Add theoretical complexity overlays:
  - O(N²)
  - O(N log N)
- Extend benchmarking with noise sensitivity tests (SNR analysis)