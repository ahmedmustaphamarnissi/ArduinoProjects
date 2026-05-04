#define ledr      PB1
#define ledy      PB5
#define trig      PB0
#define echo      PB7
#define buz       PB4
#define SW2       PB6
#define dataPin   PA5
#define latchPin  PA7
#define clockPin  PA6

int distance = 0;
long duration = 0;
long buztime = 0;

const byte SEG_BLANK = 0x00;
const byte SEG_DASH  = 0b00000001;

const byte pattern[10] = {
  0x7E, 
  0x0A, 
  0xB6,  
  0x9E,  
  0xCA,  
  0xDC,  
  0xFC,  
  0x0E,  
  0xFE,  
  0xDE   
};
void sendBoth(byte leftByte, byte rightByte) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, rightByte);
  shiftOut(dataPin, clockPin, MSBFIRST, leftByte);
  digitalWrite(latchPin, HIGH);
}

void showDash()  { sendBoth(SEG_DASH,  SEG_DASH);  }
void showBlank() { sendBoth(SEG_BLANK, SEG_BLANK); }

void showDistance(int cm) {
  if (cm < 0 || cm > 999) { sendBoth(SEG_DASH, SEG_DASH); return; }
  byte L = pattern[cm / 100]     | 0x01;  
  byte R = pattern[(cm % 100) / 10];         
  sendBoth(L, R);
  
}
void setup() {
  Serial.begin(115200);

  pinMode(ledr,        OUTPUT);
  pinMode(ledy,        OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(trig,        OUTPUT);
  pinMode(echo,        INPUT);
  pinMode(buz,         OUTPUT);
  pinMode(SW2,         INPUT_PULLUP);
  pinMode(dataPin,     OUTPUT);
  pinMode(latchPin,    OUTPUT);
  pinMode(clockPin,    OUTPUT);

  digitalWrite(ledr, LOW);
  digitalWrite(ledy, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(trig, LOW);
  

  sendBoth(pattern[8] & 0xFE, pattern[8]);
  delay(1000);
  showBlank();
}

void loop() {

  if (digitalRead(SW2) == HIGH) {

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;

    Serial.print("distance: ");
    Serial.println(distance);
    showDistance(distance);
    if (distance < 30) {
      digitalWrite(ledr, HIGH);
      digitalWrite(ledy, LOW);
      digitalWrite(LED_BUILTIN, LOW);
      tone(buz, 440);
      delay(200);
      noTone(buz);
    }
    else if (distance < 120) {
      buztime =  map(distance, 30, 120, 100, 1000);
      digitalWrite(ledr, LOW);
      digitalWrite(ledy, HIGH);
      digitalWrite(LED_BUILTIN, LOW);
      tone(buz, 440);
      delay(200);
      noTone(buz);
      delay(buztime);
    }
    else {
      digitalWrite(ledr, LOW);
      digitalWrite(ledy, LOW);
      digitalWrite(LED_BUILTIN, HIGH);
      noTone(buz);
    }
  }
  else {
    digitalWrite(ledr, LOW);
    digitalWrite(ledy, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    sendBoth(SEG_BLANK, SEG_BLANK);
    noTone(buz);
  }
  delay(100);
}