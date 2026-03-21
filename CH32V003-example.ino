/*
CH32V003 module programmed by OneCircuit and Gemini
Sat 21 Mar 2026 18:12:43 AEDT
YouTube: https://www.youtube.com/@onecircuit-as
Blog: https://onecircuit.blogspot.com/
Github: https://github.com/bovineck/
*/

const uint8_t LedArray[] = { PD4, PC4, PC3, PC2, PC1, PC0, PA2, PA1 };
const uint8_t sizeArray = 8;
uint8_t timeDelay = 150;
uint8_t breatheSpeed = 2;
int dampenedVolume = 0;
const int filterFactor = 10;

void initialise_pins(int timing) {
  for (int mypins = 0; mypins < sizeArray; mypins++) {
    pinMode(LedArray[mypins], OUTPUT);
    digitalWrite(LedArray[mypins], HIGH);
    delay(timing);
    digitalWrite(LedArray[mypins], LOW);
  }
}

void twinkle(int durationMillis) {
  unsigned long start = millis();

  while (millis() - start < durationMillis) {
    // 1. Pick a random LED
    int ledA = random(0, sizeArray);

    // 2. Randomize the "On" profile
    int peak = random(40, 180);  // Random max brightness (out of 255)
    int speed = random(1, 5);    // Random increment (1 = slow, 5 = fast)
    int timing = random(5, 12);  // Random pulse width multiplier

    // 3. Fade Up
    for (int duty = 0; duty < peak; duty += speed) {
      digitalWrite(LedArray[ledA], HIGH);
      delayMicroseconds(duty * timing);
      digitalWrite(LedArray[ledA], LOW);
      delayMicroseconds((peak - duty) * timing);
    }

    // 4. Fade Down
    for (int duty = peak; duty > 0; duty -= speed) {
      digitalWrite(LedArray[ledA], HIGH);
      delayMicroseconds(duty * timing);
      digitalWrite(LedArray[ledA], LOW);
      delayMicroseconds((peak - duty) * timing);
    }

    // 5. Random pause before the next star appears
    delay(random(50, 300));
  }
}

void setup() {
  initialise_pins(0);
  randomSeed(analogRead(0));
  Serial.begin(115200);
  delay(2000);
}

void loop() {
  Serial.println(F("Blinken de lights"));
  initialise_pins(300);
  delay(500);
  Serial.println(F("Faden de lights"));

  // Fade Up
  for (int mypins = 0; mypins < sizeArray; mypins++) {
    for (int duty = 0; duty < 255; duty++) {
      digitalWrite(LedArray[mypins], HIGH);
      delayMicroseconds(duty * 10);
      digitalWrite(LedArray[mypins], LOW);
      delayMicroseconds((255 - duty) * 10);
    }
    // Fade Down
    for (int duty = 255; duty > 0; duty--) {
      digitalWrite(LedArray[mypins], HIGH);
      delayMicroseconds(duty * 5);
      digitalWrite(LedArray[mypins], LOW);
      delayMicroseconds((255 - duty) * 2);
    }
  }
  delay(500);
  Serial.println(F("All de lights Faden"));

  // Fade Up
  for (int duty = 0; duty < 255; duty++) {
    for (int times = 0; times < breatheSpeed; times++) {  // The "Slow Down" Loop
      for (int i = 0; i < sizeArray; i++) digitalWrite(LedArray[i], HIGH);
      delayMicroseconds(duty * 10);

      for (int i = 0; i < sizeArray; i++) digitalWrite(LedArray[i], LOW);
      delayMicroseconds((255 - duty) * 10);
    }
  }

  // Fade Down
  for (int duty = 255; duty > 0; duty--) {
    for (int times = 0; times < breatheSpeed; times++) {
      for (int i = 0; i < sizeArray; i++) digitalWrite(LedArray[i], HIGH);
      delayMicroseconds(duty * 10);

      for (int i = 0; i < sizeArray; i++) digitalWrite(LedArray[i], LOW);
      delayMicroseconds((255 - duty) * 10);
    }
  }
  delay(500);
  Serial.println(F("Twinklen de lights"));
  twinkle(6000);
  delay(500);

while (1) {
    int rawVolume = analogRead(A4);
    dampenedVolume = ((dampenedVolume * 122) + (rawVolume * 6)) >> 7; // >> 7 is the same as / 128

    int response = (dampenedVolume - 50) * 9 / 650;
    if (response < 0) response = 0;
    if (response > sizeArray) response = sizeArray;

    for (uint8_t i = 0; i < sizeArray; i++) {
      digitalWrite(LedArray[i], (i < response)); 
    }

    delay(10);
  }
}
