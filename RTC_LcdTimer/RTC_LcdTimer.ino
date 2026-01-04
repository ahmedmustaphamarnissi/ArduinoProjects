//Code Created By Eng: Hossam Arafa
//http://www.youtube.com/arafamicrosystems
/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
*/

// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"

#define pb1 7 //Next
#define pb2 6 //Next Place
#define pb3 5 //Inc
#define pb4 4 //Dec

#define led A0 //LED Connected to A0&A1 Reflect the Timer Screen 1
#define gnd A1
#define led1 A2//LED Connected to A0&A1 Reflect the Timer Screen 4
#define gnd1 A3

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int ScreenNum, place1,place2,place3,place4,place5,place6,place7,place8;
char time1[8][8]={{'0','0',':','0','0',':','0','0'},{'0','0',':','0','0',':','0','0'},{'0','0',':','0','0',':','0','0'},
               {'0','0',':','0','0',':','0','0'},{'0','0',':','0','0',':','0','0'},{'0','0',':','0','0',':','0','0'},
               {'0','0',':','0','0',':','0','0'},{'0','0',':','0','0',':','0','0'}};
uint8_t hour2[8], min2[8], sec2[8];
int mask[4];
uint8_t sec1, min1, hour1, day1, month1;
uint16_t year1;
uint32_t total, total1[8], total2[8];
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //Serial.flush();
   // while (1) delay(10);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  pinMode(pb1,INPUT_PULLUP);
  pinMode(pb2,INPUT_PULLUP);
  pinMode(pb3,INPUT_PULLUP);
  pinMode(pb4,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  pinMode(gnd,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(gnd1,OUTPUT);
  digitalWrite(gnd,LOW);
  digitalWrite(gnd1,LOW);
  // Print a message to the LCD.
  //rtc.set(0, 0, 13, 20, 8, 2018); //08:00:00 24.12.2014 //sec, min, hour, day, month, year

}

void loop() 
{
  
  if(digitalRead(pb1)==LOW)
  {
    delay(10);
    while(digitalRead(pb1)==LOW);
    ScreenNum++;
    if(ScreenNum>4) ScreenNum=0;
  }

  switch(ScreenNum)
  {
    case 0:
    clock1();
    break;

    case 1:
    setScreen1();
    break;
    
    case 2:
    setScreen2();
    break;

    case 3:
    setScreen3();
    break;

    case 4:
    setScreen4();
    break;
    
  }
  check(0);
  check(1);
  Compare(0,1);
  check(2);
  check(3);
  Compare(2,3);
  check(4);
  check(5);
  Compare(4,5);
  check(6);
  check(7);
  Compare(6,7);
  
  
}

void clock1()
{
//  rtc.get(&sec1, &min1, &hour1, &day1, &month1, &year1);
  DateTime now = rtc.now();
  year1 = now.year();
  month1 = now.month();
  day1 = now.day();
  hour1 = now.hour();
  min1 = now.minute();
  sec1 = now.second();
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  if(hour1<10) lcd.print('0'); //10:00:00 //10:00:00
  lcd.print(hour1, DEC);
  lcd.print(':');
  if(min1<10) lcd.print('0');
  lcd.print(min1, DEC);
  lcd.print(':');
  if(sec1<10) lcd.print('0');
  lcd.print(sec1, DEC);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("Date: ");
  if(day1<10) lcd.print('0');
  lcd.print(day1, DEC);
  lcd.print('/');
  if(month1<10) lcd.print('0');
  lcd.print(month1);
  lcd.print('/');
  lcd.print(year1);
}

void setScreen1()
{
  lcd.setCursor(0,0);
  lcd.print("Start1: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[0][i]);
  }
  lcd.setCursor(0,1);
  lcd.print("Finish: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[1][i]);
  }
  delay(50);
  if(digitalRead(pb2)==LOW)
  {
    delay(10);
    while(digitalRead(pb2)==LOW);
    if(place1<9)
    {
      place1++;
    }else place2++;
    if(place1==3) place1=4;
    if(place1==6) place1=7;
    if(place2==3) place2=4;
    if(place2==6) place2=7;
    if(place2>8)
    {
      place1=0;
      place2=0;
    }
  }
  if(place1>0&&place1<9)
  {
    settime(0,place1);
  }else if(place2>0&&place2<9)
  {
    settime(1,place2);
  }
  switch(place1)
  {
    case 1:
    flash(1,place1);
    break;

    case 2:
    flash(2,place1);
    break;

    case 4:
    flash(4,place1);
    break;

    case 5:
    flash(5,place1);
    break;

    case 7:
    flash(7,place1);
    break;
    case 8:
    flash(8,place1);
    break;
  }

  switch(place2)
  {
    case 1:
    flash(1,place1);
    break;

    case 2:
    flash(2,place1);
    break;

    case 4:
    flash(4,place1);
    break;

    case 5:
    flash(5,place1);
    break;

    case 7:
    flash(7,place1);
    break;
    case 8:
    flash(8,place1);
    break;
  }
  
  
}


void setScreen2()
{
  lcd.setCursor(0,0);
  lcd.print("Start2: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[2][i]);
  }
  lcd.setCursor(0,1);
  lcd.print("Finish: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[3][i]);
  }
  delay(50);
  if(digitalRead(pb2)==LOW)
  {
    delay(10);
    while(digitalRead(pb2)==LOW);
    if(place3<9)
    {
      place3++;
    }else place4++;
    if(place3==3) place3=4;
    if(place3==6) place3=7;
    if(place4==3) place4=4;
    if(place4==6) place4=7;
    if(place4>8)
    {
      place3=0;
      place4=0;
    }
  }
  if(place3>0&&place3<9)
  {
    settime(2,place3);
  }else if(place4>0&&place4<9)
  {
    settime(3,place4);
  }
  switch(place3)
  {
    case 1:
    flash(1,place3);
    break;

    case 2:
    flash(2,place3);
    break;

    case 4:
    flash(4,place3);
    break;

    case 5:
    flash(5,place3);
    break;

    case 7:
    flash(7,place3);
    break;
    case 8:
    flash(8,place3);
    break;
  }

  switch(place4)
  {
    case 1:
    flash(1,place3);
    break;

    case 2:
    flash(2,place3);
    break;

    case 4:
    flash(4,place3);
    break;

    case 5:
    flash(5,place3);
    break;

    case 7:
    flash(7,place3);
    break;
    case 8:
    flash(8,place3);
    break;
  }
  
  
}

void setScreen3()
{
  lcd.setCursor(0,0);
  lcd.print("Start3: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[4][i]);
  }
  lcd.setCursor(0,1);
  lcd.print("Finish: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[5][i]);
  }
  delay(50);
  if(digitalRead(pb2)==LOW)
  {
    delay(10);
    while(digitalRead(pb2)==LOW);
    if(place5<9)
    {
      place5++;
    }else place6++;
    if(place5==3) place5=4;
    if(place5==6) place5=7;
    if(place6==3) place6=4;
    if(place6==6) place6=7;
    if(place6>8)
    {
      place5=0;
      place6=0;
    }
  }
  if(place5>0&&place5<9)
  {
    settime(4,place5);
  }else if(place6>0&&place6<9)
  {
    settime(5,place6);
  }
  switch(place5)
  {
    case 1:
    flash(1,place5);
    break;

    case 2:
    flash(2,place5);
    break;

    case 4:
    flash(4,place5);
    break;

    case 5:
    flash(5,place5);
    break;

    case 7:
    flash(7,place5);
    break;
    case 8:
    flash(8,place5);
    break;
  }

  switch(place6)
  {
    case 1:
    flash(1,place5);
    break;

    case 2:
    flash(2,place5);
    break;

    case 4:
    flash(4,place5);
    break;

    case 5:
    flash(5,place5);
    break;

    case 7:
    flash(7,place5);
    break;
    case 8:
    flash(8,place5);
    break;
  }
  
  
}

void setScreen4()
{
  lcd.setCursor(0,0);
  lcd.print("Start4: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[6][i]);
  }
  lcd.setCursor(0,1);
  lcd.print("Finish: ");
  for(int i=0;i<8;i++)
  {
    lcd.print(time1[7][i]);
  }
  delay(50);
  if(digitalRead(pb2)==LOW)
  {
    delay(10);
    while(digitalRead(pb2)==LOW);
    if(place7<9)
    {
      place7++;
    }else place8++;
    if(place7==3) place7=4;
    if(place7==6) place7=7;
    if(place8==3) place8=4;
    if(place8==6) place8=7;
    if(place8>8)
    {
      place7=0;
      place8=0;
    }
  }
  if(place7>0&&place7<9)
  {
    settime(6,place7);
  }else if(place8>0&&place8<9)
  {
    settime(7,place8);
  }
  switch(place7)
  {
    case 1:
    flash(1,place7);
    break;

    case 2:
    flash(2,place7);
    break;

    case 4:
    flash(4,place7);
    break;

    case 5:
    flash(5,place7);
    break;

    case 7:
    flash(7,place7);
    break;
    case 8:
    flash(8,place7);
    break;
  }

  switch(place8)
  {
    case 1:
    flash(1,place7);
    break;

    case 2:
    flash(2,place7);
    break;

    case 4:
    flash(4,place7);
    break;

    case 5:
    flash(5,place7);
    break;

    case 7:
    flash(7,place7);
    break;
    case 8:
    flash(8,place7);
    break;
  }
  
  
}

void settime(int Num, int place)
{
  if(digitalRead(pb4)==LOW&&place>0)
  {
    delay(10);
    while(digitalRead(pb4)==LOW);
    if(time1[Num][place-1]>='0'&&time1[Num][place-1]<'9')
    {
    time1[Num][place-1]=time1[Num][place-1]+1;
    }
  }

  if(digitalRead(pb3)==LOW&&place>0)
  {
    delay(10);
    while(digitalRead(pb3)==LOW);
    if(time1[Num][place-1]>'0'&&time1[Num][place-1]<='9')
    {
    time1[Num][place-1]=time1[Num][place-1]-1;
    }
  }
    if(time1[Num][0]>'2')
    {
      time1[Num][0]='2';
    }
    if(time1[Num][0]=='2'&&time1[Num][1]>'3')
    {
      time1[Num][1]='3';
    }
    if(time1[Num][0]=='0'&&time1[Num][1]>'9')
    {
      time1[Num][1]='9';
    }
    
    if(time1[Num][3]>'5')
    {
      time1[Num][3]='5';
    }
    if(time1[Num][4]>'9')
    {
      time1[Num][4]='9';
    }
    if(time1[Num][6]>'5')
    {
      time1[Num][6]='5';
    }
    if(time1[Num][7]>'9')
    {
      time1[Num][7]='9';
    }
}
void check(int Num)
{
  hour2[Num] = ( 10 * (time1[Num][0] - '0' ) ) + time1[Num][1] - '0';
  min2[Num] = ( 10 * (time1[Num][3] - '0' ) ) + time1[Num][4] - '0';
  sec2[Num] = ( 10 * (time1[Num][6] - '0' ) ) + time1[Num][7] - '0';
  /*
  Serial.print(Num);
  Serial.print("\t");
  Serial.println(hour2[Num]);
  */
}

void Compare(int Num1, int Num2)//20:00:00 21:00:00 21:30:00
{
  total=(uint32_t) hour1*3600+(uint32_t) min1*60+(uint32_t) sec1;
  total1[Num1]=(uint32_t) hour2[Num1]*3600+(uint32_t) min2[Num1]*60+(uint32_t) sec2[Num1];
  total2[Num1]=(uint32_t) 3600*hour2[Num2]+(uint32_t) min2[Num2]*60 +(uint32_t) sec2[Num2];

  Action();
}

void Action()
{
  
  //For First Screen Action
  if(total>=total1[0])
  {
    mask[0]=1;
  }
   
  if(total2[0]>total&&mask[0]==1)
  {
    //This part you can Add as you want to execute it
    digitalWrite(led,HIGH);// ****************
  }else
  {
    
    digitalWrite(led,LOW);// *****************
    mask[0]=0;
  }
  

  if(total>=total1[2])
  {
    mask[1]=1;
  }
   
  if(total2[2]>total&&mask[1]==1)
  {
    //This part you can Add as you want to execute it
                                  // ****************
  }else
  {
    
                                  // *****************
    mask[1]=0;
  }

  

    if(total>=total1[4])
  {
    mask[2]=1;
  }
   
  if(total2[4]>total&&mask[2]==1)
  {
    //This part you can Add as you want to execute it
                                 // ****************
  }else
  {
                                  // *****************
    mask[2]=0;
  }


    if(total>=total1[6])
  {
    mask[3]=1;
  }
   
  if(total2[6]>total&&mask[3]==1)
  {
    //This part you can Add as you want to execute it
    digitalWrite(led1,HIGH);                             // ****************
  }else
  {
    
    digitalWrite(led1,LOW);                              // *****************
    mask[3]=0;
  }
}
void flash(int inc, int placeN)
{
  if(placeN>=9)
  {
    lcd.setCursor(inc+7,1);
  }else lcd.setCursor(inc+7,0);
  lcd.print(" ");
  delay(50);
}
