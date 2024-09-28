# Variables
CC = gcc                   # Compiler
CFLAGS = -Wall             # Compiler flags, e.g., -Wall enables all compiler warnings
TARGET = main              # The name of the output executable
SRCS = src/main.c src/helpers/disk_utils.c src/helpers/encode_utils.c src/vdcreate.c src/add_file.c  src/helpers/file_utils.c src/helpers/encode.c src/helpers/math_utils.c src/ls.c src/get_file.c src/rm.c# List of all source files

# TARGET = test
# SRCS = test.c file_utils.c encode.c encode_utils.c math_utils.c


# Default target
all: $(TARGET)

# Rule to build the target executable directly from source files
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# Clean rule to remove the executable
clean:
	rm -f $(TARGET) vdisk.bin
