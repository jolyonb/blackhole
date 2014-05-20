# Compilation flags

OPTIMIZE = -O3 -march=native -flto
WARNINGS = -Wall -Wextra

CC = gcc

CFLAGS = $(OPTIMIZE) -pipe $(WARNINGS) -std=c99
LDLIBS = -lfftw3 -lfftw3l -lgsl -lblas -lgslcblas -lm

# Local overrides for build configuration

-include local.mk

# Make rules

OBJECTS = spect.o misner-sharp.o

.PHONY: all
all: test

test: spect.o misner-sharp.o

clean:
	rm -f *.o test
