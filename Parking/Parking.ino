#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,20,4);

#define red 2
#define green 3
#define trig 11
#define echo 10
#define buzzer 4
#define motionPin 8

int distance = 0;
long duration = 0;
Servo myservo;
Servo MyServo;
bool IsDoorOpen = false;
bool IsDoor2Open=false;
int CarNumbers = 0;
int EmptyPlaces;

void setup() {
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
   
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(motionPin,INPUT);

  myservo.attach(9);
  myservo.write(0);
  MyServo.attach(7);
  MyServo.write(0); 

  LcdClose();
  TurnOnRedColor();
}

void loop() {
  ReclageSonic();   // ← FIX 1: missing semicolon

  duration = pulseIn(echo, HIGH,25000); // ← FIX 2: timeout added
  if (duration == 0) return;

  distance = duration * 0.034 / 2;

  // ← FIX 3: prevent multiple counting
  if (distance <= 5) {
    if (CarNumbers == 5) {
      ParkingFull();
    } else {
      CarNumbers++;
      OpenTheDoor();
      delay(3000);
      CloseTheDoor();
    }
  }
  bool readvalue = digitalRead(motionPin);
  if(readvalue==0){
    if(CarNumbers == 0){
        ParkingEmpty();
    }
    else{
      CarNumbers--;
      OpenTheDoor2();
      delay(3000);
      CloseTheDoor2();
    }
  }

}

void OpenTheDoor() {
  IsDoorOpen = true;
  myservo.write(80);
  TurnOnGreenColor();
  LcdOpen(); 

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}

void CloseTheDoor() {
  IsDoorOpen = false;
  myservo.write(0);
  TurnOnRedColor();
  LcdClose();

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}

void OpenTheDoor2() {
  IsDoor2Open=true;
  MyServo.write(80);
  TurnOnGreenColor();
  LcdOpen(); 

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}

void CloseTheDoor2() {
  IsDoor2Open=false;
  MyServo.write(0);
  TurnOnRedColor();
  LcdClose();

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}

void ReclageSonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

void TurnOnGreenColor() {
  digitalWrite(red, LOW);
  delay(50);
  digitalWrite(green, HIGH);
}

void TurnOnRedColor() {
  digitalWrite(green, LOW);
  delay(50);
  digitalWrite(red, HIGH);
}

void LcdOpen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dr1 ");
  if(IsDoorOpen == true)lcd.print("Op/");
  else lcd.print("Cls/");
  lcd.print("Dr2 ");
  if(IsDoor2Open == true)lcd.print("Op");
  else lcd.print("Cls");

  lcd.setCursor(0, 1);
  EmptyPlaces = 5 - CarNumbers;
  lcd.print("Empty Places : ");
  lcd.print(EmptyPlaces);
}

void LcdClose() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dr1 ");
  if(IsDoorOpen == true)lcd.print("Op/");
  else lcd.print("Cls/");
  lcd.print("Dr2 ");
  if(IsDoor2Open == true)lcd.print("Op");
  else lcd.print("Cls");

  EmptyPlaces = 5 - CarNumbers;

  if (EmptyPlaces == 0) {
    lcd.print("Parking is Full");
  } else {
    lcd.print("Empty Places : ");
    lcd.print(EmptyPlaces);
  }
}

void ParkingFull() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You Can't Enter!");
  lcd.setCursor(0, 1);
  lcd.print("Parking is Full");

  delay(2000);
  LcdClose();
  TurnOnRedColor();
}
void ParkingEmpty(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("There is no Car!");
  lcd.setCursor(0, 1);
  lcd.print("Parking is Empty");

  delay(2000);
  LcdClose();
  TurnOnRedColor();
}

