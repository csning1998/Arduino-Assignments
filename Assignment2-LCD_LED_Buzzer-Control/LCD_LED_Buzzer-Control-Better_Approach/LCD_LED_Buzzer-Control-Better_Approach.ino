#include <LiquidCrystal.h>

// Define the Pin Node
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int redLED = 6;
const int yellowLED = 7;
const int greenLED = 8;
const int buzzer = 9;

void setup() {
  // Initialize the LED and Buzzer to be ready for O/P
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    input = toupper(input);
    inputHandler(input);
  }
}

/* We deal with the functionalities of the program below */

void outputInitializer() {
  lcd.clear();
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  buzzerOff();
}

void buzzerOff() {
  noTone(buzzer);
}

void ledControl(int ledPin, bool state, const char* msg) {
  digitalWrite(ledPin, state ? HIGH : LOW);
  lcd.print(msg);
}

void buzzerControl(int freq, int duration, int repeat, int interval) {
  for (int i = 0; i < repeat; i++) {
    tone(buzzer, freq, duration);
    delay(interval);
  }
  noTone(buzzer);
}

void inputHandler(char input) {
  outputInitializer();

  switch (input) {
    case 'C':
      break;
    case 'R':
      redLEDHandler();
      break;
    case 'Y':
      yellowLEDHandler();
      break;
    case 'G':
      greenLEDHandler();
      break;
    default:
      lcd.print("(422) Unprocessable Entity");
      break;
  }
}

void redLEDHandler() {
  ledControl(redLED, true, "RED ON");
  tone(buzzer, 1000);
}

void yellowLEDHandler() {
  ledControl(yellowLED, true, "YELLOW ON");
  buzzerControl(1000, 200, 5, 1000);
}

void greenLEDHandler() {
  ledControl(greenLED, true, "GREEN ON");
  buzzerControl(1000, 200, 3, 3000);
}
