CC = gcc

CFLAGS = -Wall -g -I.

ODIR = obj

DEPS = encoder.h decoder.h

_OBJ = asp_project.o encoder.o decoder.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

codec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core /*~ 
