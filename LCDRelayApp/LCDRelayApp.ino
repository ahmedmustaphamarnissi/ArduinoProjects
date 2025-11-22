

// include the library code:

#include <LiquidCrystal.h>
#define pb 7
#define gnd 8
#define in A4
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(pb,INPUT_PULLUP);
  pinMode(gnd,OUTPUT);
  pinMode(vcc,OUTPUT);
  pinMode(gnd1,OUTPUT);
  pinMode(in,OUTPUT);
  digitalWrite(vcc,HIGH);
  digitalWrite(gnd1,LOW);
  digitalWrite(gnd,LOW);
  lcd.print("Push Button");

  // Print a message to the LCD.
  
}

void loop() 
{
  if(digitalRead(pb)==LOW)
  {
    delay(10);
    lcd.setCursor(0,1);
    lcd.print("Pressed  ");
    digitalWrite(in,HIGH);
  }else
  {
    lcd.setCursor(0,1);
    lcd.print("Released");
    digitalWrite(in,LOW);
  }
}

