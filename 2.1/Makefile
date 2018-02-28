CC=gcc
CFLAGS=-I.
DEPS=input.h lex.h
OBJ=input.o lex_driver.o lex.o
ODIR=obj

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lexmake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

# stop make from doing anything with a file named `clean`
.PHONY: clean

clean:
	rm -f *.o
