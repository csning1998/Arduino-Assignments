# LED, LCD, and Buzzer Control Project Documentation

---

## 1. Hardware Overview

In this project, we use an Arduino Uno to control three LEDs (red, yellow, green), an LCD display, and a buzzer. The circuit is designed to take serial input and display corresponding outputs on the LEDs, LCD, and buzzer.

- **Red LED**: Pin 6
- **Yellow LED**: Pin 7
- **Green LED**: Pin 8
- **Buzzer**: Pin 9
- **LCD Pins**: (RS, EN, D4, D5, D6, D7) -> (12, 11, 5, 4, 3, 2)

---

## 2. Code Overview

The code below consists of several key sections, including variable declarations, setup function, loop function, and multiple utility functions that handle various aspects of the project.

### 2.1 Variable Declaration

- **Pin Definition**: We define pins for LEDs, the buzzer, and the LCD display:

  ```cpp
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  const int redLED = 6;
  const int yellowLED = 7;
  const int greenLED = 8;
  const int buzzer = 9;
  ```

  The `LiquidCrystal` object `lcd` is initialized with the control pins for the LCD, and pins for the LEDs and buzzer are also defined.

### 2.2 Setup Function

- **Initialization**: This function configures the pins as outputs and initializes the serial communication and LCD display.

  ```cpp
  void setup() {
    pinMode(redLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(buzzer, OUTPUT);
    
    lcd.begin(16, 2);
    lcd.clear();
    Serial.begin(9600);
  }
  ```

  Here, `pinMode()` is used to set each of the LED and buzzer pins to output mode. The LCD is also initialized to a 16x2 configuration, and the serial monitor is started.

### 2.3 Loop Function

- **Serial Input Handling**: The main loop listens for serial input and calls `inputHandler()` to perform actions based on the input.

  ```cpp
  void loop() {
    if (Serial.available() > 0) {
      char input = Serial.read();
      input = toupper(input);
      inputHandler(input);
    }
  }
  ```

  The `loop()` function listens for any incoming serial data. Once data is available, it converts the input to uppercase and passes it to the `inputHandler()` function.

### 2.4 Utility Functions

**1. Output Initialization (`outputInitializer()`)**

- This function turns off all LEDs, clears the LCD, and stops the buzzer.

  ```cpp
  void outputInitializer() {
    lcd.clear();
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    buzzerOff();
  }
  ```

  This ensures that each time an input is handled, all outputs are reset before setting new outputs.

**2. Buzzer Control (`buzzerOff()`)**

- Turns off the buzzer.

  ```cpp
  void buzzerOff() {
    noTone(buzzer);
  }
  ```

  This function is used to stop any sound from the buzzer.

**3. LED Control (`ledControl()`)**

- Controls the state of a specified LED and displays a message on the LCD.

  ```cpp
  void ledControl(int ledPin, bool state, const char* msg) {
    digitalWrite(ledPin, state ? HIGH : LOW);
    lcd.print(msg);
  }
  ```

  This function accepts the LED pin, a state (`true` for ON, `false` for OFF), and a message to be displayed on the LCD.

**4. Buzzer Tone Control (`buzzerControl()`)**

- Controls the buzzer to emit a tone with specified frequency, duration, repetition, and interval.

  ```cpp
  void buzzerControl(int freq, int duration, int repeat, int interval) {
    for (int i = 0; i < repeat; i++) {
      tone(buzzer, freq, duration);
      delay(interval);
    }
    noTone(buzzer);
  }
  ```

  This function is used to produce different beeping patterns for the buzzer.

**5. Input Handling (`inputHandler()`)**

- Handles user input from the serial monitor.

  ```cpp
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
  ```

  Based on the input character, different functions are called to control LEDs and the buzzer.

**6. LED Handlers (`redLEDHandler()`, `yellowLEDHandler()`, `greenLEDHandler()`)**

- **Red LED Handler (`redLEDHandler()`)**

  ```cpp
  void redLEDHandler() {
    ledControl(redLED, true, "RED ON");
    tone(buzzer, 1000);
  }
  ```
  Turns on the red LED and emits a continuous tone at 1000 Hz.

- **Yellow LED Handler (`yellowLEDHandler()`)**

  ```cpp
  void yellowLEDHandler() {
    ledControl(yellowLED, true, "YELLOW ON");
    buzzerControl(1000, 200, 5, 1000);
  }
  ```
  Turns on the yellow LED and beeps the buzzer 5 times with a 1-second interval.

- **Green LED Handler (`greenLEDHandler()`)**

  ```cpp
  void greenLEDHandler() {
    ledControl(greenLED, true, "GREEN ON");
    buzzerControl(1000, 200, 3, 3000);
  }
  ```
  Turns on the green LED and beeps the buzzer 3 times with a 3-second interval.

---

### Video Demo

The operation video has been uploaded to Google Drive:

