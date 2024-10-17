
#ifndef _MOTORS_H
#define _MOTORS_H

#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN 9
#define R_DIR_PIN 15

#define FWD LOW
#define REV HIGH

class Motors_c {
  public:

    Motors_c() {

    } 

    void initialise() {
     pinMode(L_PWM_PIN,OUTPUT);
     pinMode(L_DIR_PIN,OUTPUT);
     pinMode(R_PWM_PIN,OUTPUT);
     pinMode(R_DIR_PIN,OUTPUT);
  
     digitalWrite(L_DIR_PIN,LOW);
     digitalWrite(R_DIR_PIN,LOW);
     analogWrite(L_PWM_PIN,0);
     analogWrite(R_PWM_PIN,0);
    }
  
    void setMotorPower( float left_pwm, float right_pwm) {
    
    analogWrite(L_PWM_PIN, left_pwm);
    analogWrite(R_PWM_PIN, right_pwm);
    digitalWrite(L_DIR_PIN, LOW);
    digitalWrite(R_DIR_PIN, LOW);
    delayMicroseconds(100);
    }

    

  
};

#endif
