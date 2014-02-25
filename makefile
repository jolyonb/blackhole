
ifeq ($(USER),face)
	CC=icc
	CFLAGS=-align -Ofast -ipo -march=native -restrict -vec-report=2 -prof-dir=profiling
	LIBS= -lfftw3 -lmkl_blas95_lp64 -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_core.a $(MKLROOT)/lib/intel64/libmkl_sequential.a -Wl,--end-group
#	LIBS=-lfftw3 -mkl
else
	CC=gcc
	CFLAGS=-Ofast -flto -march=native -std=gnu99 -fprofile-dir=profiling
	LIBS=-lfftw3 -lblas -lm
endif

default: test

test: spect.o test.c
	$(CC) $(CFLAGS) spect.o test.c $(LIBS)

misner-sharp.o: misner-sharp.c
	$(CC) $(CFLAGS) -c misner-sharp.c

misner-sharp.s: misner-sharp.c
	$(CC) $(CFLAGS) -S -masm=intel misner-sharp.c

spect.o: spect.c
	$(CC) $(CFLAGS) -O2 -c spect.c

spect.s: spect.c
	$(CC) $(CFLAGS) -O2 -S -masm=intel spect.c

clean:
	rm *.o *~
