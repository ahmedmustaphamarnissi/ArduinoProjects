// Define built-in LED pin (commonly GPIO 2, but may vary)
#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set pin as output
  digitalWrite(LED_BUILTIN, HIGH); // Turn ON LED
}

void loop() {
  // Nothing needed here
}