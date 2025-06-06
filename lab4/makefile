# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -Wextra

# Source files
SRCS = Austin_testFC.c Austin_libFC.c

# Object files
OBJS = Austin_testFC.o Austin_libFC.o

# Executable name
TARGET = testApp

# Default rule: build the executable
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile Austin_testFC.c into Austin_testFC.o
Austin_testFC.o: Austin_testFC.c Austin_libFC.h
	$(CC) $(CFLAGS) -c Austin_testFC.c

# Compile Austin_libFC.c into Austin_libFC.o
Austin_libFC.o: Austin_libFC.c Austin_libFC.h
	$(CC) $(CFLAGS) -c Austin_libFC.c

# Clean rule to remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)