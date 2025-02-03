#include <Arduino.h>

void setup() {
    Serial.begin(115200); 

    Serial.println("hello world");
}

void loop() {
  Serial.println("Hello from the loop");
  delay(1000);
}