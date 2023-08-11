
CC=gcc
CFLAGS=-O2 -g -Wall -Wextra -Werror

1337:
	$(CC) $(CFLAGS) 1337.c -o $@

clean:
	rm -rf 1337
