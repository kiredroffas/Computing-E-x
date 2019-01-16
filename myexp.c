/* Erik Safford 
 * Assignment 3 - Computing e^x
 * CS 330
 * November 2018 
 *
 * This program computes f(x) = e^x = exp(x) for a given x using Taylor series. A number of
 * tracks allow us to reduce the range of x, so we can get accurate results even far from
 * the base point of the Taylor series.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_LOG2E
#define M_LOG2E   1.44269504088896340735992468100189214
#endif

#ifndef M_LN2
#define M_LN2  0.693147180559945309417232121458176568
#endif

/* From my tests in rerr.c, I determined that the smallest n between 1 and 15 such that the 
 * relative error is guaranteed to be below E = 1.19209 x 10^-7 (machine-E for floats) is
 * n = 7. 
 */

float horner(float poly[], float n, float x) {
  float result = poly[0];  // Initialize result 
  
    // Evaluate value of polynomial using Horner's method 
    for (int i=1; i<n; i++) {
      result = fmaf(result, x, poly[i]);  //fmaf() used for greater precision
    }    
    return result; 
}


float factf(float n) {  // Computes the factorial of a given n
  if (n <= 1) return 1;
    return n*factf(n-1);
}


float myexp(float x) {
  /* Computes e^x using Equation 7: f(x) = e^x = 2^m * e^u
   *                                              ^     ^
   *                                              |     |
   *                                             eq1   eq2    
   */
  

  float z = x / M_LN2;  //Equation 2
  float m = round(z);  //Equation 3
  float w = z - m;  //Equation 4
  float u = w * M_LN2; //Equation 6

  float eq1 = ldexpf(1,m);  //computes 1 * 2^m = 2^m
  
  /* Compute e^u using the series in Equation 9 (using Horner's Rule for polynomial 
   * evaluation and minimal n = 7):
   *
   * Equation 9: f(u) = 1 + u + (u^2)/2! + (u^3)/3! + ... + (u^7)/7! + (E)sub(n+1)
   *
   * Equation 11: (E)sub(n+1) = sqrt(2)/(n+1)! * (ln2/2)^(n+1)
   */

  float eSub8 = sqrt(2)/factf(8) * powf( (M_LN2/2), 8 ); //Esub(n+1) = Esub(8), n+1 = 8

  /* Evaluate value of u^7/7! + u^6/6! +u^5/5! +u^4/4! +u^3/3! +u^2/2! + u + ( 1+Esub(n+1) )
   *
   */
  
  float poly[] = {1/factf(7), 1/factf(6), 1/factf(5), 1/factf(4), 1/factf(3), 1/factf(2), 1, 1+eSub8}; //Coefficients
  float n = sizeof(poly)/sizeof(poly[0]); // n = n+1 = 7+1 = 8
  float eq2 = horner(poly, n, u); //Compute polynomial using Horner's Rule

  float exApprox = eq1 * eq2;

  return exApprox;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <number>\n", argv[0]);
    exit(1);
  }

  const float x = atof(argv[1]);
  const float y = myexp(x);

  printf("%0.9e\n", y);

  return 0;
}
