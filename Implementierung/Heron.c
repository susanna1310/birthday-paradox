#include "Heron.h"
#include "taylor.h" 
#include <stdio.h>
static unsigned long twos[10] = {2,20,200,2000,20000,200000,2000000,20000000U,200000000U,2000000000U} ;
static unsigned long sevens[10] = {7,70,700,7000,70000,700000,7000000,70000000U,700000000U,7000000000U} ;
float heron_sqrt(float n)
{  
 int nDigits = 0; 
  // count number of digits before the decimal point
  float x = n ;
  while(x>1) {
     x /= 10 ; 
     nDigits ++ ;
   }  

  // if the number of digits is odd we make the round up (exception with 0) 
    if(nDigits %2 == 0 && nDigits != 0) {
      nDigits /= 2; 
    }else {
      nDigits = nDigits/2 +1 ; 
    }

  // choose the closest initial guess
  if(absolut(twos[nDigits-1]*twos[nDigits-1] - n) < absolut(sevens[nDigits-1]*sevens[nDigits-1] - n) ) {
     x= twos[nDigits-1];
   } else {
     x = sevens[nDigits-1] ;
   } 

  // calculate x1 
   float y = (x + n/x )/2;

  //choose the accuracy level
    double e = 0.00000005 ; 

    double diff = x -y ;
    if(diff<0) 
    diff = -diff ; 
     
     // xn-xn+1 > e 
    while( diff > e  )
    {
      x = y ; 
      y = (x + n/x)/2 ;
      diff = x-y ; 
    }
    
	  return y;
}  


float birthday_eq(unsigned long n)
{
    return 0.5 + heron_sqrt(0.25 + 2 * n * 0.693147);
    // return (1 + heron_sqrt(1 + 8 * n * 0.693147)) / 2;
}