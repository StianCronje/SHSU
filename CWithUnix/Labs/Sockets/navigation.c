#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "randapi.h"

#include <sys/stat.h>
#include <fcntl.h>


int main() // Bridge
{
	char bufferw[50];
	char *sharedPipeName = "/tmp/FIFOpipe"; 

	float navDur = 0;

    // seed random number generator from given library
	seedRandGenerator();

	int fd, ret = 0;
	ret = mkfifo( sharedPipeName, 0666 );
	fd = open( sharedPipeName, O_WRONLY);

	// navigation code
	while(1)
	{
		navDur = getRandFloat() * 6;
		sprintf(bufferw, "Adjusted navigation systems: %.2fs", navDur);
		// simulate navigations work time
		sleep(navDur);
		write(fd, bufferw, sizeof(bufferw));

		sleep(30);
	}

	close(fd);

    return 0;
}