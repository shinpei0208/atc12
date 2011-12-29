#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int i;
	int mb;
	char cmd[256];
	unsigned long size;

	mb = 1;
	size = 1024 * 1024; /* 1MB */
	while (mb <= 256) {
		sprintf(cmd, "dd if=/dev/zero of=%dM_dd.dat bs=%d count=1", mb, size);

		system(cmd);

		mb *= 2;
		size *= 2;
	}

	return 0;
}

