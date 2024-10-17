#include "linesensor.h"
#include "encoders.h"
#include "WAM_Filter.h"
#include "LeakyInt.h"
#include "motors.h"

//make a leaky integrator
//Number between 0 and 1, can be changed to see performance in results
LeakyIntegrator Sensor2_Leaky(0.2); 
LeakyIntegrator Sensor3_Leaky(0.2);
LeakyIntegrator Sensor4_Leaky(0.2);

#define LED_PIN 13  // Pin to activate the orange LED
boolean led_state;  // Variable to "remember" the state
                    // of the LED, and toggle it.
//Line sensor class
LineSensor_c* Sense1;
LineSensor_c* Sense2;
LineSensor_c* Sense3;
LineSensor_c* Sense4;
LineSensor_c* Sense5;

//Motors class
Motors_c motors; 

void stopRobot() { //function to stop robot movement
     motors.setMotorPower(0,0);
}


//Sensor ranges
#define MinVal 900
#define MaxVal 1200


//For Leaky Integrator Filtering
float filteredData2;  
float filteredData3;  
float filteredData4; 
float L_mean = ((filteredData2 + filteredData3 + filteredData4)/3) ; 

 //Weighted Average Measurement
    float WMA_2 = calc_WMA(Sense2->GetLatest_F());
    float WMA_3 = calc_WMA(Sense3->GetLatest_F());
    float WMA_4 = calc_WMA(Sense4->GetLatest_F());
    float W_mean = (WMA_2 + WMA_3 + WMA_4) / 3 ;

// Raw sensor average
float R_mean = (Sense2->GetLatest_F() + Sense3->GetLatest_F() + Sense4->GetLatest_F()) /3 ;

unsigned long time;

// put your setup code here, to run once:
void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");

  time = millis();

  //Initialises Sensors 
  Sense1 = new LineSensor_c(12,11);
  Sense1->initialise(); //Not in use

  Sense2 = new LineSensor_c(A0,11);
  Sense2->initialise();

  Sense3 = new LineSensor_c(A2,11);
  Sense3->initialise();

  Sense4 = new LineSensor_c(A3,11);
  Sense4->initialise();

  Sense5 = new LineSensor_c(A4,11);
  Sense5->initialise(); //Not in use

  motors.initialise();
}


// put your main code here, to run repeatedly:
void loop() {

  //Read sensor values and prints them every 100ms
  if((millis() - time) >= 100)
  {
    //Reads sensor data
    Sense2->readSensor();
    Sense3->readSensor();
    Sense4->readSensor();
    R_mean = (Sense2->GetLatest_F() + Sense3->GetLatest_F() + Sense4->GetLatest_F()) /3 ;
    time = millis();

    //Comment out if not in use
    //Printing Raw Values
    Serial.println("Raw Values:");
    Serial.print(Sense2->GetLatest_F());
    Serial.print(" , ");
    Serial.print(Sense3->GetLatest_F());
    Serial.print(" , ");
    Serial.println(Sense4->GetLatest_F());

    //Comment out if not in use
//    Leaky Integrator Filtering
    //filteredData2 = Sensor2_Leaky.Leaky_Filter(Sense2->GetLatest_F());
    //filteredData3 = Sensor3_Leaky.Leaky_Filter(Sense3->GetLatest_F());
    //filteredData4 = Sensor4_Leaky.Leaky_Filter(Sense4->GetLatest_F());
   // L_mean = ((filteredData2 + filteredData3 + filteredData4)/3) ;

    //Printing Leaky Integrator Data
   // Serial.println("Leaky Integrator");
   // Serial.print(filteredData2);
   // Serial.print(" , ");
   // Serial.print(filteredData3);
    //Serial.print(" , ");
   // Serial.println(filteredData4);
    
    

    //Comment out if not in use
    //Weighted Average Measurement
    WMA_2 = calc_WMA(Sense2->GetLatest_F());
    WMA_3 = calc_WMA(Sense3->GetLatest_F());
    WMA_4 = calc_WMA(Sense4->GetLatest_F());
    W_mean = (WMA_2 + WMA_3 + WMA_4) / 3 ;
       
    //Printing WMA
    //Serial.println("WMA:");
   // Serial.print(WMA_2);
    //Serial.print(" , ");
   // Serial.print(WMA_3);
   // Serial.print(" , ");
   // Serial.println(WMA_4);
    
  }
  //Serial.println("L_mean:");
  //Serial.println(L_mean);
  
  R_mean = (Sense2->GetLatest_F() + Sense3->GetLatest_F() + Sense4->GetLatest_F()) /3 ;
  Serial.println(R_mean);
  if(R_mean < MinVal){
    motors.setMotorPower(20,20);
   Serial.println("moving");
  }else if(R_mean > MaxVal){
    motors.setMotorPower(20,20);
   Serial.println("moving");
  } else {
    stopRobot();
   Serial.println("stopped"); 
   delay(1000);
  }
  
  //delay(10);  // Adjust delay as needed based on your sampling rate
}
