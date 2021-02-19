#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	alarm(1);
	int i = 0;
	while (1) {
		printf("%d\n", i++);
	}
	return 0;
}