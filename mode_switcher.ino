#include <MIDI.h>

#define SCENE_BUTTON 7
#define STOMP_BUTTON 8
#define PRESET_BUTTON 9

#define SCENE_LED 10
#define STOMP_LED 11
#define PRESET_LED 12

unsigned long lastDebounceTimeScene = 0;  // the last time the output pin was toggled
unsigned long debounceDelayScene = 50;    // the debounce time; increase if the output flickers

unsigned long lastDebounceTimeStomp = 0;  // the last time the output pin was toggled
unsigned long debounceDelayStomp = 50;    // the debounce time; increase if the output flickers

unsigned long lastDebounceTimePreset = 0;  // the last time the output pin was toggled
unsigned long debounceDelayPreset = 50;    // the debounce time; increase if the output flickers

int buttonStateScene;  // the current reading from the input pin
int lastButtonStateScene = LOW;


int buttonStateStomp;  // the current reading from the input pin
int lastButtonStateStomp = LOW;

int buttonStatePreset;  // the current reading from the input pin
int lastButtonStatePreset = LOW;


MIDI_CREATE_DEFAULT_INSTANCE();
void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(SCENE_BUTTON, INPUT);
  pinMode(STOMP_BUTTON, INPUT);
  pinMode(PRESET_BUTTON, INPUT);


  pinMode(SCENE_LED, OUTPUT);
  pinMode(STOMP_LED, OUTPUT);
  pinMode(PRESET_LED, OUTPUT);

  digitalWrite(SCENE_LED, LOW);
  digitalWrite(STOMP_LED, LOW);
  digitalWrite(PRESET_LED, LOW);
  Serial.begin(115200);
}

void loop() {

  int readingScene = digitalRead(SCENE_BUTTON);
  if (readingScene != lastButtonStateScene) {
    lastDebounceTimeScene = millis();
  }

  if ((millis() - lastDebounceTimeScene) > debounceDelayScene) {
    if (readingScene != buttonStateScene) {
      buttonStateScene = readingScene;

      if (buttonStateScene == HIGH) {
        Serial.println("Scene");
        digitalWrite(SCENE_LED, HIGH);
        digitalWrite(STOMP_LED, LOW);
        digitalWrite(PRESET_LED, LOW);
        MIDI.sendControlChange(47, 1, 5);
      }
    }
  }
  lastButtonStateScene = readingScene;


  int readingStomp = digitalRead(STOMP_BUTTON);
  if (readingStomp != lastButtonStateStomp) {
    lastDebounceTimeStomp = millis();
  }

  if ((millis() - lastDebounceTimeStomp) > debounceDelayStomp) {
    if (readingStomp != buttonStateStomp) {
      buttonStateStomp = readingStomp;

      if (buttonStateStomp == HIGH) {
        Serial.println("Stomp");

        digitalWrite(SCENE_LED, LOW);
        digitalWrite(STOMP_LED, HIGH);
        digitalWrite(PRESET_LED, LOW);
        MIDI.sendControlChange(47, 2, 5);
      }
    }
  }
  lastButtonStateStomp = readingStomp;


  int readingPreset = digitalRead(PRESET_BUTTON);
  if (readingPreset != lastButtonStatePreset) {
    lastDebounceTimePreset = millis();
  }

  if ((millis() - lastDebounceTimePreset) > debounceDelayPreset) {
    if (readingPreset != buttonStatePreset) {
      buttonStatePreset = readingPreset;

      if (buttonStatePreset == HIGH) {
        Serial.println("Preset");
        digitalWrite(SCENE_LED, LOW);
        digitalWrite(STOMP_LED, LOW);
        digitalWrite(PRESET_LED, HIGH);
        MIDI.sendControlChange(47, 0, 5);
      }
    }
  }
  lastButtonStatePreset = readingPreset;
}