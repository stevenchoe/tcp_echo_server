CC = gcc
CFLAGS = -W -Wall -O2
LDFLAGS = -lm

all : tcp_echo_server

tcp_echo_server : tcp_echo_server.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean :
	rm -rf *.o
