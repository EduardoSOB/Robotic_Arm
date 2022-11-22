#include <SoftwareSerial.h>
#include <VarSpeedServo.h> 
#include <EEPROM.h> 
#include "config.h"

void setup() 
{
    serial1.begin(9600);
    Serial.begin(9600);
                  for (int i = 0; i < 120; i++)
                    {
                        data[i] = EEPROM.read(i);
                        Serial.println(data[i]);
                    }
    // arduino head max = 80, min = 0
    //arduino arm_horizontal max = 180 , min = 90;
    //arduino arm_vertical max = 180 , min = 50;
    waist.attach(6);
    arm_vertical.attach(9);
    arm_horizontal.attach(8);
    head.attach(3);

    arm_horizontal.slowmove(120,30);
    delay(1000);
    head.slowmove(40,30);
    delay(1000);
    arm_vertical.slowmove(120,30);
    delay(1000);
    waist.slowmove(0,30);
    delay(1000);

    Serial.println("ready to use!");
    checking = EEPROM.read(150);
    delay(1000);
    Serial.println(checking);
 
}

void loop() 
{  
 if (serial1.available())
  {   
      a = serial1.read();
      Serial.println(a);

      p_horizontal = &status[0];
      p_head = &status[1];
      p_vertical = &status[2];
      p_waist = &status[3];

      saving();// function used to save the servos position, and wrap it in a vector called "data"

      check_the_left_signal = a;
      pass = 0;

      if(check_the_left_signal == check_the_right_signal){pass = 1;}

      check_the_right_signal = a;

      motors('A','B',180,97,    0,0,0,1,    1);
      motors('C','D',90,40,    1,0,0,1,    2);
      motors('E','F',180,97,  1,0,0,1,    3);
      motors('G','H',180,0,  1,0,0,0,    4);
      remote_mode();
      a = 'J';
  
 }   
}
        
