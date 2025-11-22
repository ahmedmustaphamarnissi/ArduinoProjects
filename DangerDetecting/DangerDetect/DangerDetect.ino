#include <LiquidCrystal_I2C.h>

#define trig 11
#define echo 12
#define green 4
#define yellow 3
#define red 2

int distance = 0;
long duration = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Safe");

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

  SetColor(green);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.clear(); 
  lcd.setCursor(3, 0);

  // Safety logic
  if (distance >= 25) {
    lcd.print("Safe");
    SetColor(green);
  }
  else if (distance >= 20) {
    lcd.print("Little Danger");
    SetColor(yellow);
    delay(800);
    ResetColor();
  }
  else if (distance >= 15) {
    lcd.print("More Danger");
    SetColor(yellow);
    delay(200);
    ResetColor();
  }
  else if (distance >= 10) {
    lcd.print("Danger!");
    SetColor(red);
    delay(800);
    ResetColor();
  }
  else {
    lcd.print("BIG DANGER!");
    SetColor(red);
    delay(200);
    ResetColor();
  }

  delay(100);
}

void SetColor(int pinNumber) {
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(pinNumber, HIGH);
}

void ResetColor() {
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
}
