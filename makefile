CC=icc
#CFLAGS=-Ofast -flto -march=native -lfftw3 -lm -std=gnu99 -ftree-vectorizer-verbose=0
CFLAGS=-align -ipo -Ofast  -march=native -lfftw3 -restrict -vec-report=2

default: test

test: spect.o test.c
	$(CC) $(CFLAGS) spect.o test.c

misner-sharp.o: misner-sharp.c
	$(CC) $(CFLAGS) -c misner-sharp.c

spect.o: spect.c
	$(CC) $(CFLAGS) -O2 -c spect.c

spect.s: spect.c
	$(CC) $(CFLAGS) -O2 -S spect.c

clean:
	rm *.o *~
