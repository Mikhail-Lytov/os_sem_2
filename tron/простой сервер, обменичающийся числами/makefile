CC=gcc
CFLAGS=-Wall -pedantic
LD=$(CC)

BIN=tron.exe server.exe

all: clean $(BIN)

%.exe:%.c
	@echo "Build $@"
	@$(CC) $(CFLAGS) -o $@ $<
clean:
	@echo "Clean project"
	@rm -f *.exe