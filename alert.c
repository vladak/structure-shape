#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char buf[42];

	strncpy(buf, argv[1], strlen(argv[1]));

	return (0);
}
