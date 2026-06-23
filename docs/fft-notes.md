# FFT Notes

## Signal Generation

The `SignalGenerator` does **not** generate frequencies directly.

Instead, it generates signal amplitudes over time.

Example:

```cpp
gen.addSineWave(50.0, 1.0);
gen.addSineWave(120.0, 0.5);
gen.addSineWave(200.0, 0.3);
```

These sine waves are combined into a single waveform.

Each sample stored in the vector represents the total amplitude of all signal components at one instant in time.

The vector contains:

- amplitudes
- sampled at uniform time intervals

The vector does **not** contain explicit frequencies.

---

## DFT

### Time Complexity

```
O(N²)
```

### Advantages

- Easy to understand mathematically.
- Produces accurate frequency spectra.
- Excellent for learning DSP fundamentals.

### Disadvantages

- Computationally expensive.
- Poor scalability for large datasets.

---

## FFT

### Time Complexity

```
O(N log N)
```

### Advantages

- Produces the same frequency spectrum as the DFT.
- Much faster for large datasets.
- Practical for real-time signal processing.

Current implementation:

- Recursive radix-2 Cooley-Tukey FFT
- Hann window
- Peak detection

---

## Why FFT Works

The FFT does not "search" for frequencies.

Instead, it determines how strongly the sampled signal correlates with sinusoidal basis functions.

Large correlations produce peaks in the frequency spectrum.

---

## Windowing

Current implementation uses a Hann window.

Purpose:

- Reduce spectral leakage.
- Improve frequency localization.
- Smooth discontinuities at the beginning and end of the sampled signal.

Windowing intentionally reduces signal amplitude near the edges of the sampled signal.

Normalization compensates for this reduction.

---

## Current Results

The current implementation successfully detects:

- 50 Hz
- 120 Hz
- 200 Hz

using both the DFT and FFT implementations.

Minor differences in the noise floor are expected due to:

- random noise
- windowing
- normalization
- sample count