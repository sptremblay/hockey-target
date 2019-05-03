#include "FastLED.h"
#define NUM_LEDS 3
#define RESET_BUTTON_PIN 11

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

const int target1_c = A2;
const int target1_l = 2;

const int target2_c = A3;
const int target2_l = 4;

const int target3_c = A6;
const int target3_l = 6;

const int target4_c = A7;
const int target4_l = 8;

const int threshold = 100;


int reset_lastButtonState;
int reset_buttonState;
unsigned long reset_button_debounce_time = 0;

unsigned int debounce_delay = 50;


void setup() {
  Serial.begin(9600);

  pinMode(RESET_BUTTON_PIN, INPUT);

  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, target1_l>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, target2_l>(leds2, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, target3_l>(leds3, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, target4_l>(leds4, NUM_LEDS);

  initTarget(leds1);
  initTarget(leds2);
  initTarget(leds3);
  initTarget(leds4);
}

void loop() {
  // put your main code here, to run repeatedly:

  int reading1 = digitalRead(RESET_BUTTON_PIN);
  if (reset_buttonState != reset_lastButtonState) {
    reset_button_debounce_time = millis();
  }

  if ((millis() - reset_button_debounce_time) > debounce_delay) {
    reset_buttonState = reading1;
    if (reset_buttonState != reset_lastButtonState &&
        reset_buttonState == HIGH) {
      Serial.println("Reset");
      initTarget(leds1);
      initTarget(leds2);
      initTarget(leds3);
      initTarget(leds4);
    }
  }

  int sensorReading = analogRead(target1_c);
  if (sensorReading >= threshold) {
    Serial.println("Touched Target 1");
    touchedTarget(leds1);
  }

  sensorReading = analogRead(target2_c);
  if (sensorReading >= threshold) {
    Serial.println("Touched Target 2");
    touchedTarget(leds2);
  }


  sensorReading = analogRead(target3_c);
  if (sensorReading >= threshold) {
    Serial.println("Touched Target 3");
    touchedTarget(leds3);
  }

  sensorReading = analogRead(target4_c);
  if (sensorReading >= threshold) {
    Serial.println("Touched Target 4");
    touchedTarget(leds4);
  }
}

void initTarget(CRGB* led) {
  led[0] = CRGB::Red;
  led[1] = CRGB::Red;
  led[2] = CRGB::Red;
}

void touchedTarget(CRGB* led) {
  led[0] = CRGB::Blue;
  led[1] = CRGB::Blue;
  led[2] = CRGB::Blue;
}
