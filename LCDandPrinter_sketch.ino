#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define TX_PIN 6 
#define RX_PIN 5 

#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

SoftwareSerial mySerial(RX_PIN, TX_PIN); 
Adafruit_Thermal printer(&mySerial);     

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  printer.begin(); 
  mySerial.begin(9600);
  
  lcd.begin (20,4,LCD_5x8DOTS);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  Serial.begin(9600);

}

void loop()
{
  //This line checked that communication between the arduino 
  //and the pi was working correctly
  Serial.println("Hello Pi");
  if (Serial.available())
  {
     LCD(Serial.readString());
     
     Printer(mySerial.readString());
  }
  delay(1000);
}

void LCD(String n)
{
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.print(n);
}

void Printer(String n)
{
  printer.println(n);

  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults 
}
