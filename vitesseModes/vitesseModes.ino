#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#define btn 2

Stepper myStepper(2048, 8, 10, 9, 11);
LiquidCrystal_I2C lcd(0x27,20,4);

int speedMode = 1;
int speed=5;

void setup() {
  lcd.init();
  lcd.backlight();
  myStepper.setSpeed(speed);
  myStepper.step(2048);
  pinMode(btn,INPUT_PULLUP);
  LcdPrint(speedMode);

}

void loop() {
  if(!digitalRead(btn)){
    if(speedMode!=3){
      speed+=5;
      myStepper.setSpeed(speed);
      speedMode ++;
    }
    else{
      speed=5;
      myStepper.setSpeed(speed);
      speedMode =1;
    }
    LcdPrint(speedMode);
    delay(200);
  }
  
}
void LcdPrint(int vitesseMode) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vitesse mode: ");
  if(vitesseMode==1)
    lcd.print("1");
  else if(vitesseMode==2)
    lcd.print("2");
  else
  lcd.print("3");

}

