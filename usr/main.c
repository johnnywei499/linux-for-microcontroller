#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LED_NAME "/dev/led"

int main(int argc, char **argv) 
{
	int ret;
	int fd;
	int value = 0;
 
	fd = open(LED_NAME, O_RDWR);
	if (fd < 0) {
		printf("open dev fail: %s\n", LED_NAME);
		return -1;
	}

	while (1) {
		value = !value;
		write(fd, &value, 1);
		usleep(1000000);
	}

	close(fd);
	return 0;
}
