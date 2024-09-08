#include "taylor.h"
float absolut ( float x) {
  if (x >0) return x ;
  else return -x ;
} 
float taylor(float x)
{
  if(x==0)
  return 0 ;
  int k = 0;
  // calculating the number of digits of x and transforming x to x=x* 10^-(k) so that x is between 0 and 1
  while (x > 1)
  {
    x /= 10;
    k++;
  }
  x = x - 1;
  float coeff = 0.5;
  float res = 1.f + 0.5f * x;
  float pow_x = x * x;
  float prevres=res;
  // calculating the terms of taylor series and accumulating the result of 50 terms
  for (int i = 2; i <= 50; i++)
  {

  
    coeff = (absolut(coeff) * (2 * i - 3)) / (2 * i); // here the coefficients of the terms will be calculated using the previous term  
   
    if (i % 2 == 0)
    {
      coeff *= -1; //when the index of the term is even  the coefficient is negative 
    }
    res += coeff * pow_x; //summing the terms of the taylor series 
    pow_x *= x;
    if(res==prevres) // the loop will be interrupted if the precision of the result is not changing 
    break;
    else
      prevres=res;

  }
  
  // x is reconverted to the original format 
  if (k % 2 == 0)
  {
    for (int j = 0; j < (k / 2); j++) // when the number of digits even is , the result will be multiplied with sqrt(10^k)=10^(k/2)
      res *= 10;
    }
  else
  {
    for (int j = 0; j < (k - 1) / 2; j++) // when the number of digits is uneven the result will be multiplied with sqrt(10^k)=10^(k/2)*sqrt(10) 
      res *= 10;
    res *= 3.16227766017f;
  }
  return res;
}
 float birthday_eq_V2(unsigned long n)
{
  return 0.5 + taylor(0.25 + 2 * n * 0.693147);
}
