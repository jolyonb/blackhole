
#ifeq ($(USER),jolyon)
#	CC=icc
#	CFLAGS=-align -Ofast -ipo -march=native -restrict -vec-report=0 -prof-dir=profiling 
#	LIBS=-lfftw3l /lib/libgsl.a -lmkl_blas95_lp64 -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_core.a $(MKLROOT)/lib/intel64/libmkl_sequential.a -Wl,--end-group -lpthread
#	LIBS=-L/opt/intel/mkl/lib/intel64 -lfftw3 -lfftw3l -lgsl -mkl
#else
	CC=gcc
	CFLAGS=-Ofast -flto -march=native -std=gnu99 -fprofile-dir=profiling 
	LIBS=-lfftw3 -lfftw3l -lgsl -lblas -lgslcblas -lm
#endif

default: test
all: test

test: spect.o test.c
	$(CC) $(CFLAGS) spect.o test.c $(LIBS)

misner-sharp.o: misner-sharp.c
	$(CC) $(CFLAGS) -c misner-sharp.c

misner-sharp.s: misner-sharp.c
	$(CC) $(CFLAGS) -S -masm=intel misner-sharp.c

spect.o: spect.c
	$(CC) $(CFLAGS) -Ofast -c spect.c

spect.s: spect.c
	$(CC) $(CFLAGS) -O2 -S -masm=intel spect.c

clean:
	rm -f *.o a.out *~
