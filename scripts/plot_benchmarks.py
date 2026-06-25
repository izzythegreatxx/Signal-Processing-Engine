import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("plots/benchmark_results.csv")

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
plt.show()