#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "randapi.h"

#include <sys/stat.h>
#include <fcntl.h>

void PrintCurrentTime();


int main() // Bridge
{
	char bufferr[50];
	char *sharedPipeName = "/tmp/FIFOpipe";

    // seed random number generator from given library
	seedRandGenerator();

	int fd, ret = 0;
	ret = mkfifo( sharedPipeName, 0666 );
	fd = open( sharedPipeName, O_RDONLY);

	printf("Bridge starting...\n");
	PrintCurrentTime();
	printf("\n");

	// repeats until it fails to read
	while(ret != 0)
	{
		ret = read( fd, bufferr, sizeof(bufferr));
		printf("%s\n", bufferr);
		PrintCurrentTime();
		printf("\n");
	}

	return 0;
}


void PrintCurrentTime()
{
	time_t currentTime;
	struct tm *curTime;	
	time(&currentTime);
	curTime = localtime(&currentTime);
	printf("Current Time: %d:%d:%d\n", curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
	return;
}