#include <stdint.h>
// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _LINESENSOR_H
#define _LINESENSOR_H

//Define sensor pins
#define Sensor1 A0  //left
#define Sensor2 A2  //centre
#define Sensor3 A3  //right
#define Sensor4 A4  //rightmost
#define Sensor5 12  //leftmost
#define EMIT_PIN 11 //emit pin
#define BLACK_THRES 1200 //threshold to detect colour is black

/*
  Any value above 1500 will be considered white
*/

// Class to operate the linesensor(s).
class LineSensor_c 
{
  
  private:
    //Variables only used whithin the class declared here
    unsigned long startTime;
    unsigned long endTime;
    unsigned long elapsedTime;
    unsigned long elapsedTimePrev;
    uint32_t timetotal;
    uint8_t pin_Rx;
    uint8_t pin_Tx;
    uint16_t sense_val;
    bool is_black;
    uint16_t count;
    uint16_t AveNum = 20;

  public:
  
    // Constructor, must exist.
    LineSensor_c(uint8_t Rx_pin, uint8_t Tx_pin);
    // Initialises sensors
    void initialise(void);
    // Reads Values from Sensors
    void readSensor(void);
    //Obtains latest value from sensors
    uint16_t GetLatestVal(void);
    //Checks if value obtained correspond to line (black) or !line (white)
    bool isBlack(void);
    //obtains last value from sensors
    float GetLatest_F(void){return (float)elapsedTime;}

};



#endif
