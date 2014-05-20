# Compilation flags

OPTIMIZE = -O3 -march=native -flto
WARNINGS = -Wall -Wextra

CC = gcc

CFLAGS = $(OPTIMIZE) -pipe $(WARNINGS) -std=c99
LDLIBS = -lfftw3 -lfftw3l -lgsl -lblas -lgslcblas -lm

# Local overrides for build configuration

-include local.mk

# Make rules

OBJECTS = test.o spect.o misner-sharp.o

.PHONY: all
all: test

test: $(OBJECTS)

clean:
	rm -rf *.o test .deps

# Fancy dependency stuff

DEPDIR = .deps

%.o : %.c
	@mkdir -p .deps && $(CC) -MM $(CFLAGS) $< -MP -MF $(DEPDIR)/$*.P
	$(COMPILE.c) -o $@ $<

-include $(OBJECTS:%.o=$(DEPDIR)/%.P)
