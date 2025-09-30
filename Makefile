# Default rule to build the target
all: ray-tracer

# Link object files to create the executable
ray-tracer: main.c
	gcc -o ray-tracer main.c

# Clean up build files
clean:
	rm -f ray-tracer *.ppm