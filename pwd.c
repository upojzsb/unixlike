#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	printf("%s\n", getcwd(NULL, 0));
	exit(EXIT_SUCCESS);
}
