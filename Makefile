# Default rule to build the target
# all: ray-tracer

# Link object files to create the executable
#ray-tracer: main.c
# gcc -o ray-tracer main.c

# Clean up build files
#clean:
#	rm -f ray-tracer *.ppm


# Compiler
CC = g++

# Compiler flags
CFLAGS = -O3 -fopenmp -std=c++11

# Target executable
TARGET = ray-tracer

# Source files
srcs = src/*.cc

# Dependency files
deps = include/*.h

# Default rule to build the target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(srcs) $(deps)
	$(CC) $(CFLAGS) -o $(TARGET) $(srcs)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET) *.ppm *.png
