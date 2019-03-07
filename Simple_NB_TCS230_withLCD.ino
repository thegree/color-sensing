#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LCD Pins
//SDA to A4
//SCL to A5

// TCS230 sensor reading example
//
// This is just to show basic functionality without calibration.
// Utilises the non-blocking version of the reading function.
// Output uses the Serial console.
//
#include <MD_TCS230.h>
#include <FreqCount.h>

// Pin definitions
#define  S2_OUT  12
#define  S3_OUT  13
#define  OE_OUT   8    // LOW = ENABLED 

MD_TCS230  CS(S2_OUT, S3_OUT, OE_OUT);

void setup() 
{
   lcd.begin(16,2);                
 lcd.home ();                   
 lcd.print(" Color Sensor ");  
 lcd.setCursor ( 0, 1 );        
 lcd.print (" Test Color   ");
 delay ( 2000 );
 lcd.clear();
 
  Serial.begin(57600);
    CS.begin();
}

void readSensor()
{
  static  bool  waiting;
  
  if (!waiting)
  {
    CS.read();
    waiting = true;
  }
  else
  {
    if (CS.available()) 
    {
      colorData  rgb;
      
      CS.getRGB(&rgb);
      lcd.clear();
      lcd.home ();
      lcd.print("RGB ");
      lcd.print(rgb.value[TCS230_RGB_R]);
      lcd.print(",");
      lcd.print(rgb.value[TCS230_RGB_G]);
      lcd.print(",");
      //lcd.setCursor(0,1);
      lcd.print(rgb.value[TCS230_RGB_B]);
      //lcd.print("]");
      delay ( 1000 );
      
      waiting = false;
    }
  }
}


void loop() 
{
  readSensor();
}
