#include "definitions.h"

/* The following function computes:

r=K(k)/K'(k) where
K is the complete elliptic integral of the first kind,
K' is the complementary complete elliptic integral of the first kind

This simple routine was given to my by Dan  - it is one hell
of a lot simplier than the routine in the numerical recipes book

*/

double K_over_Kdash(double k)
{
  double kp, r, kf;
  kp = sqrt(1.0-pow(k,2.0));
  r = 1.0;
  kf=(1.0+k)/(1.0+kp);
  while(kf != 1.0)
  {
    r = r*kf;
    k = 2.0*sqrt(k)/(1.0+k);
    kp = 2.0*sqrt(kp)/(1.0+kp);
    kf=(1.0+k)/(1.0+kp);
  }
  return(r);
}
