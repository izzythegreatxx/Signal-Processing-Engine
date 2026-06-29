CXX = g++
CXXFLAGS = -std=c++17 -Iinclude $(shell python3-config --includes) -I$(shell python3 -c "import numpy; print(numpy.get_include())")
LDFLAGS = $(shell python3-config --embed --ldflags)

SRC = src/main.cpp src/FIRFilter.cpp src/BenchmarkSuite.cpp src/CSVExporter.cpp src/PeakDetection.cpp src/SignalGenerator.cpp src/FFTProcessor.cpp
TARGET = signal_app

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)