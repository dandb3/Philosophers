#include <unistd.h>
#include <sys/stat.h>

char *argv[] = {"./a", NULL};

int main(void) {
	struct stat	buf;

	stat("a", &buf);
	if (buf.st_mode & 0010000)
		write(1, "is directory\n", 13);
	return 0;
}