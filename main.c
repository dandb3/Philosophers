#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/stat.h>

char *argv[] = {"./a", NULL};

int main(void) {
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	printf("%ld:%ld\n", tv.tv_sec, tv.tv_usec);
	return 0;
}