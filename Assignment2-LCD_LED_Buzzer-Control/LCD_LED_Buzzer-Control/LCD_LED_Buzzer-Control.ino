#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the Pin Node
LiquidCrystal_I2C lcd(0x27,16,2);

const int redLED = 6;
const int yellowLED = 7;
const int greenLED = 8;
const int buzzer = 9;


void setup() {
  // Initialize the LED and Buzzer to be ready for O/P
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Hello World!");
}

void loop() {
  if(Serial.available() > 0){
    char input = Serial.read();
    if(input == '\n' || input == '\r') {
      return;
    }
    input = toupper(input);
    inputHandler(input);
  }
}

/* We deal with the functionalities of the program below */

void outputInitializer(){
  lcd.clear();
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  noTone(buzzer);
}

void inputHandler(char input){
  outputInitializer();
  Serial.print("Input_char is "); Serial.println(input);

  switch (input) {
    case 'C':
      break;
    
    case 'R':
      digitalWrite(redLED, HIGH);
      lcd.print("RED ON");
      tone(buzzer, 1000);
      break;
    
    case 'Y':
      digitalWrite(yellowLED, HIGH);
      lcd.print("YELLOW ON");
      for (int i = 0; i < 5; i++){
        tone(buzzer, 1000, 200);
        delay(1000);
      }
      noTone(buzzer);
      break;
    
    case 'G':
      digitalWrite(greenLED, HIGH);
      lcd.print("GREEN ON");
      for (int i = 0; i < 5; i++) {
        tone(buzzer, 1000, 200);  
        delay(3000); 
      }
      noTone(buzzer);
      break;
    
    default:
      lcd.print("(422) Unprocessable Entity");
      break;
  }
}
