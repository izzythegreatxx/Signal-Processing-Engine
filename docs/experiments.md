# DSP Experiments

## Experiment 1 - Verifying the DFT


### Objective

Verify that the DFT correctly detects known frequencies.

### Signal

- 50 Hz
- 120 Hz
- 200 Hz
- Random noise

### Result

The DFT correctly identified all three dominant frequencies.

---

## Experiment 2 - Hann Window

### Objective

Apply a Hann window before computing the DFT.

### Observation

The frequency spectrum became cleaner with reduced spectral leakage.

Peak amplitudes changed due to windowing and required normalization using the window sum.

---

## Experiment 3 - Recursive FFT

### Objective

Replace the DFT with a recursive Cooley-Tukey FFT.

### Observation

The FFT identified the same dominant frequencies as the DFT:

- 50 Hz
- 120 Hz
- 200 Hz

Minor differences appeared in the lower-energy portions of the spectrum.

Possible causes include:

- Random noise
- Different normalization
- Hann window
- Sample size (1024 samples)

### Conclusion

The FFT produces equivalent frequency detection while significantly improving computational efficiency.

Future work includes benchmarking execution time for increasing FFT sizes.