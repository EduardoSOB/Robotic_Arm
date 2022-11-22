#ifndef __config_h__
#define __config_h__

#include <SoftwareSerial.h>  //biblioteca que me permite usar mais de uma porta Serial, uma ficou pro monitor e outra pro modulo bluetooth
//#include <Servo.h>
#include <VarSpeedServo.h>       //biblioteca que faz o motor girar devagar
#include <EEPROM.h>              //biblioteca da EEPRO
SoftwareSerial serial1(12, 13);  // RX, TX
VarSpeedServo head;
VarSpeedServo arm_horizontal;
VarSpeedServo arm_vertical;
VarSpeedServo waist;

byte head_count = 0;
byte vertical = 0;
byte horizontal = 0;
byte waist_count = 0;

byte for_horizontal = 0;
byte for_head = 30;
byte for_vertical = 60;
byte for_waist = 90;

bool check_head, check_horizontal, check_vertical, check_waist = 0, block = 0, pass = 0;
byte  b, c;
char a, check_the_left_signal, check_the_right_signal = 'z';
byte cont[4] = { 0 };
byte status[4] = { 120, 40, 120, 0 };
byte data[120] = { 0 };
byte checking, timer = 0;
byte *p_horizontal = &status[0], *p_head = &status[1], *p_vertical = &status[2], *p_waist = &status[3], *p_checking = &checking;
#define eeprom_size 500
byte rotate_left, rotate_right = 0, going = 0; 
float testing_stuff = 0;

void detaching(bool horizontal_bool, bool head_bool, bool vertical_bool, bool waist_bool) {
  check_horizontal = horizontal_bool;
  check_head = head_bool;
  check_vertical = vertical_bool;
  check_waist = waist_bool;

  waist.attach(6);  
  arm_vertical.attach(9); 
  arm_horizontal.attach(8);
  head.attach(3);

  if (check_horizontal == 1) {
    arm_horizontal.detach();
  }


  if (check_head == 1) {
    head.detach();
  }


  if (check_vertical == 1) {
    arm_vertical.detach();
  }


  if (check_waist == 1) {
    waist.detach();
  }
}


void motors(char left, char right, int max, int min , bool n1, bool n2, bool n3, bool n4, byte motor) 
{
 

  if (a == left || a == right) 
  {
    
      if (motor == 1) 
      {
        b = 0;
        Serial.println("motor 1");      
      }
            if (motor == 2) 
            {
              Serial.println("motor 2"); 
              b = 1;
            }
                  if (motor == 3) 
                  {
                    Serial.println("motor 3"); 
                    b = 2;
                  }
                        if (motor == 4)
                        {
                            Serial.println("motor 4"); 
                            b = 3;
                          }
      Serial.println(check_the_right_signal);
        Serial.println(check_the_left_signal);
      Serial.println(pass);
      
        detaching(n1, n2, n3, n4);   
        testing_stuff = status[b];

      while (a == left) 
   {
        if (serial1.available()){a = serial1.read();}
        Serial.println(a);
        testing_stuff = testing_stuff + 0.1;
              if (testing_stuff >= max) 
              {
                  testing_stuff = max;
              }

          if(motor == 1)
        { 
            arm_horizontal.slowmove(testing_stuff, 30); 
            head.slowmove(status[1], 30); 
            arm_vertical.slowmove(status[2], 30); 
            waist.slowmove(status[3], 30);       
        }
        if(motor == 2)
        {
            head.slowmove(testing_stuff, 30);
            arm_vertical.slowmove(status[2], 30); 
            waist.slowmove(status[3], 30); 
            arm_horizontal.slowmove(status[0], 30);        
        }
        if(motor == 3)
        {
            arm_vertical.slowmove(testing_stuff, 30); 
            arm_horizontal.slowmove(status[0], 30);  
            head.slowmove(status[1], 30); 
            waist.slowmove(status[3], 30);     
        }      
        if(motor == 4)
        {
            waist.slowmove(testing_stuff, 30); 
            arm_horizontal.slowmove(status[0], 30);  
            head.slowmove(status[1], 30); 
            arm_vertical.slowmove(status[2], 30);  
        }   
    }

        while(a == right) 
          {
            if (serial1.available()){a = serial1.read();}
            Serial.println(a);
            testing_stuff = testing_stuff - 0.1;
            if (testing_stuff <= min) { testing_stuff = min; }
            
        
                if(motor == 1)
                {
                    arm_horizontal.slowmove(testing_stuff, 30); 
                    head.slowmove(status[1], 30); 
                    arm_vertical.slowmove(status[2], 30); 
                    waist.slowmove(status[3], 30);       
                }
                if(motor == 2)
                {
                    head.slowmove(testing_stuff, 30);
                    arm_vertical.slowmove(status[2], 30); 
                    waist.slowmove(status[3], 30); 
                    arm_horizontal.slowmove(status[0], 30);        
                }
                if(motor == 3)
                {
                    arm_vertical.slowmove(testing_stuff, 30); 
                    arm_horizontal.slowmove(status[0], 30);  
                    head.slowmove(status[1], 30); 
                    waist.slowmove(status[3], 30);     
                }
                if(motor == 4)
                { 
                    waist.slowmove(testing_stuff, 30); 
                    arm_horizontal.slowmove(status[0], 30);  
                    head.slowmove(status[1], 30); 
                    arm_vertical.slowmove(status[2], 30);  
                }   
           }

              status[b] = testing_stuff;
              check_the_right_signal = 'z';  
  }
  
}

void saving(void) 
{
  if (a == 'X') 
  {

    if (checking < 30) 
    {

      cont[0] = checking;
      cont[1] = checking + 30;
      cont[2] = checking + 60;
      cont[3] = checking + 90;
      checking++;
      EEPROM.write(150, checking);

      EEPROM.write(cont[0], status[0]);
      data[cont[0]] = EEPROM.read(cont[0]);

      EEPROM.write(cont[1], status[1]);
      data[cont[1]] = EEPROM.read(cont[1]);

      EEPROM.write(cont[2], status[2]);
      data[cont[2]] = EEPROM.read(cont[2]);

      EEPROM.write(cont[3], status[3]);
      data[cont[3]] = EEPROM.read(cont[3]);
      Serial.println("saving");
      delay(1000);
      Serial.println("salvo!");
    }
  }
}

void executing(void) 
{
  for_horizontal = 0;
  for_head = 30;
  for_vertical = 60;
  for_waist = 90;
  
  detaching(1,0,0,1);
  
  Serial.println(*p_checking);
  for (int i = 0; i < *p_checking; i++)
 {

    detaching(1, 0, 0, 1);
    arm_vertical.slowmove(data[for_vertical], 30);
    delay(1000);
    p_vertical = data[for_vertical];
    Serial.print(data[for_vertical]);
    for_vertical++;
    *p_vertical = data[for_vertical];  
    Serial.print("   ");    
   
    detaching(1, 0, 0, 0);
  
    waist.slowmove(data[for_waist], 30);
     delay(1000);
    p_waist = data[for_waist];
    Serial.print(data[for_waist]);
    for_waist++;
    *p_waist = data[for_waist];
    Serial.print("   ");
   
    delay(1000);

    detaching(0, 0, 0, 1);
    arm_horizontal.slowmove(data[for_horizontal], 30);
     delay(1000);
    p_horizontal = data[for_horizontal];
    Serial.print(data[for_horizontal]);
    for_horizontal++;
    *p_horizontal = data[for_horizontal];
    Serial.print("   ");
    
    detaching(1, 0, 0, 1);
    head.slowmove(data[for_head], 30);
    delay(1000);      
    p_head = data[for_head];
    Serial.print(data[for_head]);
    for_head++;
    *p_head = data[for_head];
    Serial.print("   "); 
  }
}


void show(void) 
{
  
    Serial.println("");
    Serial.print("horizontal : ");
    for (int i = 0; i < 30; i++)
    {
      data[i] = EEPROM.read(i);
      Serial.print(data[i]);
      Serial.print("  ");
    }
      Serial.println("");
      Serial.print("head : ");
    for (int i = 30; i < 60; i++) 
    {
      data[i] = EEPROM.read(i);
      Serial.print(data[i]);
      Serial.print("  ");
    }
      Serial.println("");
      Serial.print("vertical : ");
    for (int i = 60; i < 90; i++)
     {
      data[i] = EEPROM.read(i);
      Serial.print(data[i]);
      Serial.print("  ");
     }
      Serial.println("");
      Serial.print("waist : ");
    for (int i = 90; i < 120; i++) 
    {
      data[i] = EEPROM.read(i);
      Serial.print(data[i]);
      Serial.print("  ");
    }
}

void remote_mode(void) 
{
    bool kk;
    if (a == 'Y')
 {
    delay(600);
    c = 0;
    a = 'Z';
    Serial.println("************************************************************************************************************************************************************************************");
    Serial.println("Remoto: aperte quadrado");
    Serial.println("");
    Serial.println("local: aperte X");
    Serial.println("");
    Serial.println("exibir tabela de posicoes: aperte circulo");
    Serial.println("");
    Serial.println("limpar tabela de posicoes: aperte triangulo");
    Serial.println("");
    Serial.println("30 segundos pra escolher uma opcao!");
    Serial.println("************************************************************************************************************************************************************************************");
    timer = 30;
    while (c == 0) 
        {
          timer--;
          Serial.print(timer);
          Serial.print(" ");
          delay(1000);
          if (serial1.available()) 
          {
              a = serial1.read();
          }
          if (timer == 0)
          {
              timer = 30;
              Serial.println("o tempo expirou!");
              a = 'k';
          }

          if(a == 'H' && c == 0)
          {
          for(int i = 0; i<eeprom_size; i++)
          {
              EEPROM.write(i,0);                  
          }
              checking = EEPROM.read(150);
              Serial.println("limpo!");
              c = 200;
          }      

          if (a == 'F' && c == 0 )
          {
              executing();
              kk = 0;
              c = 200;
          }

          if (a == 'G' && c == 0)
          {
              show();
              c = 200;
              kk = 0;
          }

          if (a == 'E' && c == 0) 
          {
              c = 200;
              kk = 1;
              Serial.println("modo remoto iniciado com sucesso!");
              delay(1000);
          }
        }
    while (a == 'E' )
    {
          executing();
      if (serial1.available()) 
      {
        kk = 0;
        Serial.println(a);
      }
    }
  }
}




#endif