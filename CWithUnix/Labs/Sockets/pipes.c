#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "randapi.h"

void PrintCurrentTime();

int main() // Bridge
{
    char bufferw[50], bufferr[50];

	float lifeDur = 0, envDur = 0, navDur = 0;

    // create pipe
    int myPipe[2];
    if (pipe(myPipe) < 0)
    {
		printf("Pipe creation unsuccessful!\n");
		exit(1);
    }

    // seed random number generator
    seedRandGenerator();

    if (fork() == 0) // create navigation, child 1
    {
		close(myPipe[0]);
		if (fork() == 0) // create life support – child 2
		{
			// life support code

			lifeDur = getRandExponential() * 5;
			sprintf(bufferw, "Adjusted life support systems: %.2fs", lifeDur);
			sleep(lifeDur);
			write(myPipe[1], bufferw, 50);

			envDur = getRandExponential() * 4;
			sprintf(bufferw, "Adjusted Environment control systems: %.2fs", envDur);
			sleep(envDur);
			write(myPipe[1], bufferw, 50);
		}
		else
		{
			// navigation code
			navDur = getRandFloat() * 6;
			sprintf(bufferw, "Adjusted navigation systems: %.2fs", navDur);
			sleep(navDur);
			write(myPipe[1], bufferw, 50);
		}

	//END CHILD - termination of life function.
    }
    else // bridge
    {
		printf("Bridge starting...\n");
		PrintCurrentTime();
		printf("\n");
		close(myPipe[1]);

		read(myPipe[0], bufferr, 50);
		printf("%s\n", bufferr);
		PrintCurrentTime();
		printf("\n");

		read(myPipe[0], bufferr, 50);
		printf("%s\n", bufferr);
		PrintCurrentTime();
		printf("\n");

		read(myPipe[0], bufferr, 50);
		printf("%s\n", bufferr);
		PrintCurrentTime();
		printf("\n");
    }

    return 0;
} // end program


void PrintCurrentTime()
{
	time_t currentTime;
	struct tm *curTime;	
	time(&currentTime);
	curTime = localtime(&currentTime);
	printf("Current Time: %d:%d:%d\n", curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
	return;
}