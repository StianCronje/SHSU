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

	float lifeDur = 0, envDur = 0;

    // seed random number generator from given library
	seedRandGenerator();

	int fd, ret = 0;
	ret = mkfifo( sharedPipeName, 0666 );
	fd = open( sharedPipeName, O_WRONLY);

	// life support code
	while(1)
	{
		lifeDur = getRandExponential() * 5;
		sprintf(bufferw, "Adjusted life support systems: %.2fs", lifeDur);
		// simulate life support work time
		sleep(lifeDur);
		write(fd, bufferw, sizeof(bufferw));

		envDur = getRandExponential() * 4;
		sprintf(bufferw, "Adjusted Environment control systems: %.2fs", envDur);
		// simulate environment control work time
		sleep(envDur);
		write(fd, bufferw, sizeof(bufferw));

		sleep(30);
	}

	close(fd);

	return 0;
}