# Variables
CC = gcc                   # Compiler
CFLAGS = -Wall             # Compiler flags, e.g., -Wall enables all compiler warnings
TARGET = main              # The name of the output executable
SRCS = main.c disk_utils.c encode_utils.c vdcreate.c add_file.c  # List of all source files

# Default target
all: $(TARGET)

# Rule to build the target executable directly from source files
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean rule to remove the executable
clean:
	rm -f $(TARGET)
