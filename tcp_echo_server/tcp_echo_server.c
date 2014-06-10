#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 1024
void error_exit(char *message);

int main(int argc, char **argv) {
	int server_fd;
	int client_fd;
	char message[BUFSIZE];
	int str_len, ret;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int client_addr_size;

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	server_fd = socket(PF_INET, SOCK_STREAM, 0);

	if (server_fd == -1)
		error_exit("socket() error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	ret = bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
	if (ret == -1)
		error_exit("bind() error");

	ret = listen(server_fd, 5);
	if (ret == -1)
		error_exit("listen() error");

	client_addr_size = sizeof(client_addr);
	client_fd = accept(server_fd, (struct sockaddr*) &client_addr,
			&client_addr_size);

	if (client_fd == -1)
		error_exit("accept() error");

	while ((str_len = read(client_fd, message, BUFSIZE)) != 0) {
		write(client_fd, message, str_len);
		write(1, message, str_len);
	}
	close(client_fd);
	close(server_fd);
	return 0;
}

void error_exit(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
