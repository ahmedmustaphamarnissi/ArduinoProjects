 
// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>
#define led 13
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char StorePass[]="123456789425";
int i=0,count=0,number=sizeof(StorePass)-1;
char pass[sizeof(StorePass)-1];

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Enter the Pass");
  lcd.setCursor(0, 1);
  pinMode(led,OUTPUT);
}

void loop() 
{
  char key = keypad.getKey();
  
  if (key>='0'&&key!='D')
  {
    lcd.print('*');
    pass[i]=key;
    i++;
  }else if(key=='D')
  {
    if(i==number)
    {
      for(int j=0;j<number;j++)
      {
        if(pass[j]==StorePass[j])count++;
      }
      if(count==number)
      {
        lcd.clear();
        digitalWrite(led,HIGH);
        lcd.setCursor(0,0);
        lcd.print("Correct Pass    ");
        delay(2000);
        i=0;
        count=0;
        lcd.setCursor(0,0);
        lcd.print("Enter the Pass");
        lcd.setCursor(0,1);
      }else
      {
        printt();
      }
    }else
    {
      printt();
    }
  }
}

void printt()
{
        lcd.clear();
        digitalWrite(led,LOW);
        lcd.setCursor(0,0);
        lcd.print("Wrong Pass     ");
        delay(2000);
        i=0;
        count=0;
        lcd.setCursor(0,0);
        lcd.print("Enter the Pass");
        lcd.setCursor(0,1);
}

