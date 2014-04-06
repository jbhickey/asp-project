CC = gcc
CFLAGS = -Wall -g -I.

ODIR = obj

DEPS = file_io.h encoder.h prediction.h

_OBJ = asp_project.o file_io.o encoder.o prediction.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

asp_project: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core /*~ 
