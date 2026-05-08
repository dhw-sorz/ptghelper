CC = gcc
PREFIX = /usr/local

all:
	$(CC) -o unmask unmask.c

install:
	install -Dm755 unmask $(PREFIX)/bin/unmask

uninstall:
	rm -f $(PREFIX)/bin/unmask

clean:
	rm -f unmask
