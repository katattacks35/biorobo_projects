#include "WAM_Filter.h"

//weights for moving average calculation
const float weights[] = {0.1, 0.2, 0.3, 0.2, 0.1};

//array to store sensor reading values
float sense2_val[array_size];
float sense3_val[array_size];
float sense4_val[array_size];

//calculate weighted moving average
float calc_WMA(float senseVal)
{
  //shifts values to the right as the come in the array until full
  for(int i = array_size -1; i > 0; i--)
  {
    sense2_val[i] = sense2_val[i-1];
  }
  //add new value to array
  sense2_val[0] = senseVal;

  //calculate WMA
  float weightSum = 0;
  for(int i = 0; i < array_size; i++)
  {
    weightSum += sense2_val[i] * weights[i];
  }
  return weightSum;
}
