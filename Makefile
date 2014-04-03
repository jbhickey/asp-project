CC=gcc
CFLAGS=-Wall -g

ODIR=obj

_DEPS = file_io.h
DEPS = $(patsubst %,/%,$(_DEPS))

_OBJ = asp_project.o file_io.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

asp_project: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core /*~ 
