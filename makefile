CC=icc
#CFLAGS=-Ofast -flto -march=native -lfftw3 -lm -std=gnu99
CFLAGS=-align -Ofast  -march=native -lfftw3 -restrict -vec-report=2

default: test

test: spect.o test.c
	$(CC) $(CFLAGS) spect.o test.c

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
