#include "Arduino.h"
#include "linesensor.h"

//Constructor, must exist
//Give value names that only will be used within the class
LineSensor_c::LineSensor_c(uint8_t Rx_pin, uint8_t Tx_pin)
{
  pin_Rx = Rx_pin;
  pin_Tx = Tx_pin;
  sense_val = 0;
  count = 0;
  timetotal = 0;
}

//Initialises the sensors
void LineSensor_c::initialise(void)
{
  //Line Sensor
  pinMode(pin_Tx, INPUT);
  pinMode(pin_Rx, INPUT);
}

//Reads values from sensors
void LineSensor_c::readSensor(void)
{
  //Save last vale
  elapsedTimePrev = elapsedTime;
  //Emit pin
  pinMode(pin_Tx, OUTPUT);
  digitalWrite(pin_Tx, HIGH);
  //Line sensors
  pinMode(pin_Rx, OUTPUT);
  digitalWrite(pin_Rx, HIGH);

  delayMicroseconds(10);

  pinMode(pin_Rx, INPUT);
  startTime = micros(); //set timer for reading line sensors
  while( digitalRead(pin_Rx)== HIGH)
  {
    endTime = micros(); //end timer for reading line sensors
    if((endTime - startTime) >= 10000)  //checks time elapsed between start and end to break code in case of error
    {
      break;
    }
  }
  
  pinMode(pin_Tx, INPUT);
  elapsedTime = endTime - startTime;  //calculates time taken to read sensor

  timetotal += elapsedTime;
  count++;
  if(count == AveNum)
  {
    count = 0;
    sense_val = (uint16_t)(((float)timetotal) / AveNum);
    timetotal = 0;
  }

}

//Obtains latest value from sensors
uint16_t LineSensor_c::GetLatestVal(void)
{
  return sense_val;
}

//Checks if value obtained correspond to line (black) or !line (white)
bool LineSensor_c::isBlack(void)
{
  if (sense_val >= BLACK_THRES)   //value obtained bigger than threshold for black
  {
    is_black = true;  //sensor value is black
  }
  else
  {
    is_black = false; //sensor value !black (white)
  }
  return is_black;  //return bool obtained for implementation in FSM
}
