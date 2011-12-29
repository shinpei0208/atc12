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
	char fname[64];
	char cmd[256];
	unsigned long size;
	double sec, mbps;
	unsigned long us_start, us_end;
	struct timeval tv_start, tv_end;

	mb = 1;
	size = 1024 * 1024; /* 1MB */
	while (mb <= 256) {
		sprintf(fname, "%dM.dat", mb);
		sprintf(cmd, "cp -f %dM.dat %dM_copy.dat", mb, mb);

		/* START! */
		gettimeofday(&tv_start, NULL);

		system(cmd);

		/* END! */
		gettimeofday(&tv_end, NULL);

		us_end = tv_end.tv_usec + tv_end.tv_sec * 1000000;
		us_start = tv_start.tv_usec + tv_start.tv_sec * 1000000;
		sec = (double) (us_end - us_start) / 1000000.0;
		mbps = (double) (size / (1024.0 * 1024.0)) / sec;
	
		printf("Copy %dMB: %f Mbps\n", mb, mbps);

		mb *= 2;
		size *= 2;
	}

	return 0;
}

