#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 10001

int main() {
	int server = socket(PF_INET, SOCK_STREAM, 0);
	int client;

	if (server == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if (bind(server, &server_addr, sizeof(server_addr)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(server, 5) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	socklen_t client_addr_size = sizeof(client_addr);
	client = accept(server, &client_addr, &client_addr_size);

	if (client == -1) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	char buf[0x4000];
	size_t r;

	while (1) {
		printf("> ");
		fgets(buf, 0x400, stdin);
		r = strlen(buf);

		if (buf[r-1] == 10) {
			buf[r-1] = 0;
			--r;
		}

		write(client, buf, strlen(buf)+1);

		if (!strcmp(buf, "exit")) {
			break;
		}

		r = read(client, buf, 0x4000);
		write(1, buf, r);
	}

	close(client);
	close(server);

	return 0;
}
