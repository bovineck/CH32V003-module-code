/*
CH32V003 module programmed by OneCircuit and Gemini
Sat 21 Mar 2026 18:12:43 AEDT
YouTube: https://www.youtube.com/@onecircuit-as
Blog: https://onecircuit.blogspot.com/
Github: https://github.com/bovineck/
*/

const uint8_t LedArray[] = { PD4, PC4, PC3, PC2, PC1, PC0, PA2, PA1 };
const uint8_t sizeArray = 8;
const int timeDelay = 300;
const uint8_t breatheSpeed = 2;
const int filterFactor = 6;  // to dampen the sound readings
int dampenedVolume = 0;

// VU Meter Tuning
const int MIC_FLOOR = 50;     // Ignore noise below this level
const int MIC_CEILING = 450;  // Full scale (all LEDs on) at this level
const int micRange = MIC_CEILING-MIC_FLOOR;
const uint8_t LED_COUNT = 8;  // Total number of LEDs

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
    int ledA = random(0, sizeArray);
    int peak = random(40, 180);  // Random max brightness (out of 255)
    int speed = random(1, 5);    // Random increment (1 = slow, 5 = fast)
    int timing = random(5, 12);  // Random pulse width multiplier

    for (int duty = 0; duty < peak; duty += speed) {
      digitalWrite(LedArray[ledA], HIGH);
      delayMicroseconds(duty * timing);
      digitalWrite(LedArray[ledA], LOW);
      delayMicroseconds((peak - duty) * timing);
    }

    for (int duty = peak; duty > 0; duty -= speed) {
      digitalWrite(LedArray[ledA], HIGH);
      delayMicroseconds(duty * timing);
      digitalWrite(LedArray[ledA], LOW);
      delayMicroseconds((peak - duty) * timing);
    }
    delay(random(50, timeDelay));
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
  initialise_pins(timeDelay);
  delay(timeDelay);
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
  delay(timeDelay);
  Serial.println(F("All de lights Faden"));

  for (int direction = 0; direction < 2; direction++) {
    for (int dutyCycle = 0; dutyCycle < 255; dutyCycle++) {
      int duty = (direction == 0) ? dutyCycle : (255 - dutyCycle);
      for (int times = 0; times < breatheSpeed; times++) {
        for (int i = 0; i < sizeArray; i++) digitalWrite(LedArray[i], HIGH);
        delayMicroseconds(duty * 10);
        for (int i = 0; i < sizeArray; i++) digitalWrite(LedArray[i], LOW);
        delayMicroseconds((255 - duty) * 10);
      }
    }
  }

  delay(timeDelay);
  Serial.println(F("Twinklen de lights"));
  twinkle(20 * timeDelay);
  delay(timeDelay);

  while (1) {
    int rawVolume = analogRead(A4);
    dampenedVolume = ((dampenedVolume * (128 - filterFactor)) + (rawVolume * filterFactor)) >> 7;
    int response = (dampenedVolume - MIC_FLOOR) * (LED_COUNT + 1) / micRange;
    if (response < 0) response = 0;
    if (response > sizeArray) response = sizeArray;
    for (uint8_t i = 0; i < sizeArray; i++) {
      digitalWrite(LedArray[i], (i < response));
    }
    delay(10);
  }
}