# Variables
CC = gcc           # Compiler
CFLAGS = -Wall     # Compiler flags, e.g., -Wall enables all compiler warnings
TARGET = main      # The name of the output executable
SRCS = main.c vdcreate.c encode_utils.c# List of all source files
OBJS = $(SRCS:.c=.o)  # Convert .c files to .o files
 
 # Default target
 all: $(TARGET)
 
 # Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm
 
 # Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
 
 # Clean rule to remove the object files and the executable
clean:
	rm -f $(OBJS) $(TARGET) vdisk.bin
