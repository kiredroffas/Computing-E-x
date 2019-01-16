/* Erik Safford
 * Assignment 3 - Computing e^x
 * CS 330
 * November 2018 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double fact(double n) {  // Computes the factorial of a given n 
  if (n <= 1) return 1;
  return n*fact(n-1);
}

int main() {
  /* Prints n and the corresponding upper bound for the relative error using Equation 12 for
   * n = 1 to 15 (using doubles). From these values I determine the smallest n such that the
   * relative error is quaranteed to be below E = 1.19209 x 10^-7 (machine-E for floats). 
   *
   * Equation 12: relative error = (2/(n+1)!)*(ln2/2)^(n+1)
   *                                    ^         ^
   *                                    |         |
   *                                   eq1       eq2
   */

  for(int n=1; n <= 15; n++) {
    int nPlusOne = n+1;  
    double eq1 = 2 / fact(nPlusOne);
    printf("n: %d eq1 = %0.13lf\n",n,eq1);

    double eq2 = pow( (log(2)/2), nPlusOne ); 
    printf("n: %d eq2 = %0.13lf\n",n,eq2);

    double relError = eq1 * eq2;
    printf("n: %d relError = %0.13lf\n",n,relError);

    if(relError < 0.000000119209) {  
      printf("BELOW E\n");
    }
    else {
      printf("ABOVE\n");
    }
  }
    
  return 0;
}
