
#include <LiquidCrystal_I2C.h>
#define sw1 11 //Decrease Button
#define sw2 10 //Increase Button
#define sw3 9 //Move Left Button
#define sw4 8 //Move Right Button

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char st[]="00/00/0000";
int count=0;

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.print("      Date      ");
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  pinMode(sw3,INPUT_PULLUP);
  pinMode(sw4,INPUT_PULLUP);
}


void loop() 
{
  lcd.setCursor(3, 1);
  lcd.print(st);
  delay(150);
  if(digitalRead(sw4)==LOW)
  {
    delay(10);
    while(digitalRead(sw4)==LOW);
    count++;
    if(count<=0) count=0;
    if(count==3) count=4;
    if(count==6) count=7;
    if(count>=11) count=0;
  }

  if(digitalRead(sw3)==LOW)
  {
    delay(10);
    while(digitalRead(sw3)==LOW);
    count--;
    if(count==3) count=2;
    if(count==6) count=5;
    //if(count==11) count=0;
  }
  if(digitalRead(sw2)==LOW&&count>0)
  {
    delay(10);
    while(digitalRead(sw2)==LOW);
    if(st[count-1]>='0'&&st[count-1]<'9')
    {
    st[count-1]=st[count-1]+1;
    }
    //Date Format Conditions
    if(st[0]>'3')st[0]='3';
    if(st[0]=='3'&&st[1]>'1')st[1]='1';
    if(st[3]>'1')st[3]='1';
    if(st[3]=='1'&&st[4]>'2')st[4]='2';
  }

  if(digitalRead(sw1)==LOW&&count>0)
  {
    delay(10);
    while(digitalRead(sw1)==LOW);
    if(st[count-1]>'0'&&st[count-1]<='9')
    {
    st[count-1]=st[count-1]-1;
    }
    if(st[0]>'3')st[0]='3';
    if(st[0]=='3'&&st[1]>'1')st[1]='1';
    if(st[3]>'1')st[3]='1';
    if(st[3]=='1'&&st[4]>'2')st[4]='2';
  }
  switch(count)
  {
    case 1:
    flash(1);
    break;

    case 2:
    flash(2);
    break;

    case 4:
    flash(4);
    break;

    case 5:
    flash(5);
    break;

    case 7:
    flash(7);
    break;
    case 8:
    flash(8);
    break;
    case 9:
    flash(9);
    break;
    case 10:
    flash(10);
    break;
  }
  
}

void flash(int inc)
{
  lcd.setCursor(inc+2,1);
  lcd.print(" ");
  delay(50);
}
