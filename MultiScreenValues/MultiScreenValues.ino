//www.youtube.com/arafamicrosystems
#include <LiquidCrystal_I2C.h>
#define pb1 8 // Decrement
#define pb2 9 // Increment
#define pb3 10 // Prev
#define pb4 11 // Next
#define an A0 // Potentiometer
int count=0, value0, value1, value2, value3;
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,20,4);
void setup() 
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(pb1,INPUT_PULLUP);
  pinMode(pb2,INPUT_PULLUP);
  pinMode(pb3,INPUT_PULLUP);
  pinMode(pb4,INPUT_PULLUP);
}

void loop() 
{
  if(digitalRead(pb4)==LOW)
  {
    delay(10);
    while(digitalRead(pb4)==LOW);
    count++;
    if(count>3) count=3;
  }

  if(digitalRead(pb3)==LOW)
  {
    delay(10);
    while(digitalRead(pb3)==LOW);
    count--;
    if(count<0) count=0;
  }

  switch(count)
  {
    case 0:
    page0();
    break;

    case 1:
    page1();
    break;

    case 2:
    page2();
    break;

    case 3:
    page3();
    break;
  }

}

void page0()
{
  lcd.setCursor(0,0);
  lcd.print("Value     ");
  lcd.setCursor(13,1);
  lcd.print("1/4");
  check();
  lcd.setCursor(0,1);
  lcd.print(value0);
  lcd.print("      ");
  
}

void page1()
{
  lcd.setCursor(0,0);
  lcd.print("Value     ");
  lcd.setCursor(13,1);
  lcd.print("2/4");
  check();
  lcd.setCursor(0,1);
  lcd.print(value1);
  lcd.print("      ");
}

void page2()
{
  lcd.setCursor(0,0);
  lcd.print("Value     ");
  lcd.setCursor(13,1);
  lcd.print("3/4");
  check();
  lcd.setCursor(0,1);
  lcd.print(value2);
  lcd.print("      ");
}

void page3()
{
  lcd.setCursor(0,0);
  lcd.print("Value     ");
  lcd.setCursor(13,1);
  lcd.print("4/4");
  check();
  lcd.setCursor(0,1);
  lcd.print(value3);
  lcd.print("      ");
}

void check()
{
  if(digitalRead(pb2)==LOW)
  {
    delay(analogRead(an));
    switch(count)
    {
      case 0:
      value0++;
      break;

      case 1:
      value1++;
      break;

      case 2:
      value2++;
      break;

      case 3:
      value3++;
      break;
      
    }
  }

  if(digitalRead(pb1)==LOW)
  {
    delay(analogRead(an));
    switch(count)
    {
      case 0:
      value0--;
      if(value0<0) value0=0;
      break;

      case 1:
      value1--;
      if(value1<0) value1=0;
      break;

      case 2:
      value2--;
      if(value2<0) value2=0;
      break;

      case 3:
      value3--;
      if(value3<0) value3=0;
      break;
      
    }
  }
}

