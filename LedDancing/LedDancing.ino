#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// ===== LED PINS =====
int red[]    = {2, 3, 4};
int yellow[] = {5, 6, 7};
int green[]  = {8, 9, 10};

#define btn 12

// ===== VARIABLES =====
int mode = 0;
int lastMode = -1;

bool lastBtn = HIGH;
unsigned long lastTime = 0;
const int debounceDelay = 200;

int stepIndex = 0;   // animation step
unsigned long lastAnim = 0;
const int animDelay = 150;

// ===== FUNCTIONS =====
void allOff() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(red[i], LOW);
    digitalWrite(yellow[i], LOW);
    digitalWrite(green[i], LOW);
  }
}

void updateLCD() {
  if (mode != lastMode) {
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("MODE ");
    lcd.print(mode + 1);
    lastMode = mode;
    stepIndex = 0;   // reset animation on mode change
  }
}

// ===== SETUP =====
void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(red[i], OUTPUT);
    pinMode(yellow[i], OUTPUT);
    pinMode(green[i], OUTPUT);
  }

  pinMode(btn, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

// ===== LOOP =====
void loop() {
  // ----- Button -----
  bool btnState = digitalRead(btn);
  if (btnState == LOW && lastBtn == HIGH &&
      millis() - lastTime > debounceDelay) {
    mode++;
    if (mode > 3) mode = 0;
    lastTime = millis();
  }
  lastBtn = btnState;

  updateLCD();

  // ----- Animation timing -----
  if (millis() - lastAnim < animDelay) return;
  lastAnim = millis();

  allOff();

  // ===== LED DANCE MODES =====
  if (mode == 0) {
    // MODE 1: Left → Right
    digitalWrite(red[stepIndex], HIGH);
    digitalWrite(yellow[stepIndex], HIGH);
    digitalWrite(green[stepIndex], HIGH);
    stepIndex = (stepIndex + 1) % 3;
  }

  else if (mode == 1) {
    // MODE 2: Right → Left
    int idx = 2 - stepIndex;
    digitalWrite(red[idx], HIGH);
    digitalWrite(yellow[idx], HIGH);
    digitalWrite(green[idx], HIGH);
    stepIndex = (stepIndex + 1) % 3;
  }

  else if (mode == 2) {
    // MODE 3: Color chase
    if (stepIndex < 3) {
      digitalWrite(red[stepIndex], HIGH);
    } else if (stepIndex < 6) {
      digitalWrite(yellow[stepIndex - 3], HIGH);
    } else {
      digitalWrite(green[stepIndex - 6], HIGH);
    }
    stepIndex = (stepIndex + 1) % 9;
  }

  else if (mode == 3) {
    // MODE 4: Bounce
    static int dir = 1;
    digitalWrite(red[stepIndex], HIGH);
    digitalWrite(yellow[stepIndex], HIGH);
    digitalWrite(green[stepIndex], HIGH);

    stepIndex += dir;
    if (stepIndex == 2 || stepIndex == 0) dir = -dir;
  }
}
