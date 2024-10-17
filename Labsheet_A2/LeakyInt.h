#ifndef LeakyInt_h
#define LeakyInt_h

#include <Arduino.h>

class LeakyIntegrator {
private:
  float a_coeff;
  float Prev_Out;

public:

  LeakyIntegrator(float a);
  float Leaky_Filter(float in);

};

#endif
