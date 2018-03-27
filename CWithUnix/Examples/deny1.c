#include <stdio.h>
#include <wait.h>
#include <unistd.h>

int main( ) {
 int knt = 1, k;
 
  while (knt < 5) {
      printf("start new child\n");
      if( fork( ) == 0 ) {  // child created (forked) successfully

         // START CHILD
         for(k = 0; k < 5; k++) printf("catch me if you can!\n");
         sleep (0);  // force the process scheduler into action, e.g., sleep(1) to sleep one second
         //END CHILD - termination of life function.
 
      } else {
         printf("Back in parent\n");
         //fork( );  // If feeling extra mean!
      }
      knt++;
  }

  return 0; 
}