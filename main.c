#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
	char buf[0x20];
	memset(buf, 0, 0x20);

	read(0, buf, 0x20);
	write(1, buf, strlen(buf));

	return 0;
}