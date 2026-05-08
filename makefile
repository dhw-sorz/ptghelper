CC = gcc
PREFIX = /usr/local

all:
	$(CC) -o ptghelper ptghelper.c

install:
	install -Dm755 ptghelper $(PREFIX)/bin/ptghelper

uninstall:
	rm -f $(PREFIX)/bin/ptghelper

clean:
	rm -f ptghelper
