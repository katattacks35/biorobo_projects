#include "LeakyInt.h"


LeakyIntegrator::LeakyIntegrator(float a)
{
  a_coeff = a;
}


float LeakyIntegrator::Leaky_Filter(float in)
{
  float RetVal;

  RetVal = (1 - a_coeff)*Prev_Out;
  RetVal += (in * a_coeff);

  Prev_Out = RetVal;
  return RetVal;
}
