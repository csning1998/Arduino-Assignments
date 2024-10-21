#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int RED_LED = 6;
const int YELLOW_LED = 7;
const int GREEN_LED = 8;
const int BUZZER = 9;

const int BUZZER_FREQ = 1000;
const int BUZZER_DURATION = 200;
const int BUZZER_REPEAT = 5;
const int YELLOW_INTERVAL = 1000;
const int GREEN_INTERVAL = 3000;

volatile bool keepBuzzing = false;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  lcd.init();          
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Awaiting Input...");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == '\n' || input == '\r') {
      return;
    }
    inputHandler(input);
  }

  if (keepBuzzing) {
    tone(BUZZER, BUZZER_FREQ);
  }
}

/* We deal with the functionalities of the program below */

void resetOutputs() {
  lcd.clear();
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  keepBuzzing = false;
  buzzerOff();
}

void buzzerOff() {
  noTone(BUZZER);
}

void ledControl(int ledPin, bool state) {
  digitalWrite(ledPin, state ? HIGH : LOW);
}

void displayMessage(const char* msg) {
  lcd.clear();
  lcd.print(msg);
}

void initialMessage(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Awaiting Input...");
}

void buzzerController(int freq, int duration, int repeat, int interval) {
  Serial.println("Start Buzzing");
  Serial.print("num of freq: "); Serial.println(freq);
  Serial.print("num of duration: "); Serial.println(duration);
  Serial.print("num of repeat: "); Serial.println(repeat);
  Serial.print("num of interval: "); Serial.println(interval);
  
  for (int i = 0; i < repeat; i++) {
    tone(BUZZER, freq, duration);
    delay(duration);
    delay(interval);
  }
  buzzerOff();
}

void ledController(int ledPin, const char* msg, int repeat, int interval) {
  ledControl(ledPin, true);
  displayMessage(msg);
  
  Serial.println("Start Lightening");
  Serial.print("LED PIN is: "); Serial.println(ledPin);
  Serial.print("num of repeat: "); Serial.println(repeat);
  Serial.print("num of interval: "); Serial.println(interval);
  
  if (repeat > 0 && interval > 0) {
    buzzerController(BUZZER_FREQ, BUZZER_DURATION, repeat, interval);
  } else if (repeat == -1) {
    keepBuzzing = true;
  } else {
    Serial.println("Invalid parameter(s) received.");
  }
}

void inputHandler(char input) {
  resetOutputs();
  input = toupper(input);
  Serial.println("=== Session Started ===");
  
  switch (input) {
    case 'C':
      break;
    case 'R':
      ledController(RED_LED, "RED ON", -1, -1);
      break;
    case 'Y':
      ledController(YELLOW_LED, "YELLOW ON", BUZZER_REPEAT, YELLOW_INTERVAL);
      initialMessage();
      break;
    case 'G':
      ledController(GREEN_LED, "GREEN ON", BUZZER_REPEAT, GREEN_INTERVAL);
      initialMessage();
      break;
    default:
      displayMessage("(422) Unprocessable Entity");
      Serial.println("Invalid command received.");
      delay(3000);
      initialMessage();
      break;
  }
}
