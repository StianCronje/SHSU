#ifndef __RAND_API_H
#define __RAND_API_H

/* generate seed from clock */
extern void seedRandGenerator(  );  

/*  0.0 <= random float < 1.0  */
extern float getRandFloat(  );    

/*  0 thru (max - 1)  */
extern int getRandInteger( int max ); 

/*  exponential interarrival time, multiply by mean */
extern float getRandExponential( );  

#endif /* __RAND_API_H */