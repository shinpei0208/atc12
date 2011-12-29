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
	FILE *fp;
	char fname[64];
	unsigned char *buf;
	unsigned long size;
	double sec, mbps;
	unsigned long us_start, us_end;
	struct timeval tv_start, tv_end;

	system("rm -fr *.dat");

	mb = 1;
	size = 1024 * 1024; /* 1MB */
	while (mb <= 256) {
		buf = malloc(size);
		for (i = 0; i < size; i++)
			buf[i] = i % 256;

		sprintf(fname, "%dM.dat", mb);

		/* START! */
		gettimeofday(&tv_start, NULL);

		fp = fopen(fname, "w");
		if (!fp)
			printf("failed to open %s\n", fname);

		/* write to file */
		fwrite(buf, size, 1, fp);
		fflush(fp);

		fclose(fp);

		/* END! */
		gettimeofday(&tv_end, NULL);

		free(buf);

		us_end = tv_end.tv_usec + tv_end.tv_sec * 1000000;
		us_start = tv_start.tv_usec + tv_start.tv_sec * 1000000;
		sec = (double) (us_end - us_start) / 1000000.0;
		mbps = (double) (size / (1024.0 * 1024.0)) / sec;
	
		printf("Write %dMB: %f Mbps\n", mb, mbps);

		mb *= 2;
		size *= 2;
	}

	return 0;
}

