import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("plots/benchmark_results.csv")
ms = pd.read_csv("plots/magnitude_spectrum.csv")
td = pd.read_csv("plots/time_domain_signal.csv")


# DFT vs FFT
plt.figure()
plt.plot(df["Sample_Size"], df["DFT_Time (ms)"], label="DFT (O(N^2))")
plt.plot(df["Sample_Size"], df["FFT_Time (ms)"], label = "FFT (O(N log N))")


plt.xlabel("Sample Size (N)")
plt.ylabel("Time (ms)")
plt.title("DFT vs FFT Performance Scaling")
plt.legend()
plt.grid()

plt.savefig("plots/timing.png")

# Speedup
plt.figure()
plt.plot(df["Sample_Size"], df["Speedup"], label="Speedup (DFT / FFT)")

plt.xlabel("Sample Size (N)")
plt.ylabel("Speedup")
plt.title("FFT Speedup vs DFT")
plt.grid()


plt.savefig("plots/speedup.png")


# Magnitude Spectrum for a specific sample size
sample_size = 1024
plt.figure()
plt.plot(ms["Frequency_Hz"], ms["Magnitude"], label=f"Magnitude Spectrum (N={sample_size})")
plt.xlabel("Frequency Bin")
plt.ylabel("Magnitude")
plt.title(f"Magnitude Spectrum for Sample Size {sample_size}")
plt.grid()
plt.savefig("plots/magnitude_spectrum.png")


# Time-Domain Signal
plt.figure()
plt.plot(td["Time_s"], td["Amplitude"], label="Time-Domain Signal")
plt.xlabel("Time_s")
plt.ylabel("Amplitude")
plt.title("Time-Domain Signal")
plt.grid()
plt.savefig("plots/time_domain_signal.png")