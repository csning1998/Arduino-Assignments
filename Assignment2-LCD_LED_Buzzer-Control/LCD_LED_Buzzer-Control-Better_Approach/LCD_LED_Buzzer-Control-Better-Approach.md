
### Abstract

This project demonstrates the control of an Arduino system utilizing LEDs, an I2C LCD, and a buzzer. Through serial input, users can interact with the system, triggering different behaviors for each component. The system manages multiple functionalities such as turning on specific LEDs, controlling the buzzer with adjustable frequency, duration, and intervals, and displaying corresponding messages on the LCD. The project is designed with modular functions to facilitate easy expansion and maintenance, ensuring a smooth interaction between hardware components based on user inputs.


### Criteria

Refer to the table below for the expected output of the buzzer, LCD, and LED based on user input values.


## Preparation

### Import Libraries

In this assignment, as we are implementing I2C control for the LCD, we will need to import the necessary libraries, including `<Wire.h>` for communication between devices and the circuit board, and `<LiquidCrystal_I2C.h>` for controlling the LCD via the I2C communication protocol. We will also initialize the LCD, which has an I2C address of 0x27 and dimensions of 16 columns by 2 rows, as shown below:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
```

### Variable Declarations

We will also define the pin numbers for the buzzer, LCD, and LEDs:

```cpp
const int RED_LED = 6;
const int YELLOW_LED = 7;
const int GREEN_LED = 8;
const int BUZZER = 9;
```

The curcuit diagram of this implementation is shown below. 

![Circuit Diagram corresponding to this program](https://raw.githubusercontent.com/csning1998/Arduino-Assignments/refs/heads/main/Assignment2-LCD_LED_Buzzer-Control/LCD_LED_Buzzer-Control-Better_Approach/Circuit_Diagram.png "Circuit Diagram corresponding to this program")

Reference: https://www.tinkercad.com/things/5rIyDSxOSNt-assignment2-lcdledbuzzer?sharecode=CIG4u1ELGAVlzIMVaE91icyVWZxpKHHCOTl0qU4CiQc

Additionally, we will define several parameters that are used by the circuit components:

```cpp
const int BUZZER_FREQ = 1000;
const int BUZZER_DURATION = 200;
const int BUZZER_REPEAT = 5;
const int YELLOW_INTERVAL = 1000;
const int GREEN_INTERVAL = 3000;
```

Since we need the buzzer to keep buzzing when the input is 'R', and we want to be able to stop it through external input (such as 'C'), we use `volatile` to declare the boolean variable `keepBuzzing`, initializing it to `false`:

```cpp
volatile bool keepBuzzing = false;
```

## Function Definitions

As per the assignment criteria, we need to control all three components, so we define the necessary functions to manage each one as follows:

### Resetting Outputs

After completing one task, the system should be reset before proceeding to the next task, in order to avoid exceptional situations. This is handled by the following function:

```cpp
void resetOutputs() {
  lcd.clear();
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  keepBuzzing = false;
  buzzerOff();
}
```

The `buzzerOff()` function is used to stop the buzzer. It is kept simple for future flexibility and extensibility:

```cpp
void buzzerOff() {
  noTone(BUZZER);
}
```

### LCD Control

We want the LCD to display different statuses, such as "Awaiting Input," "Processing," and "Output Complete."

The `initialMessage()` function indicates that the system is ready to receive input:

```cpp
void initialMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Awaiting Input...");
}
```

In the `displayMessage()` function, we use a pointer to the message string `msg` to manage what is displayed on the LCD. Since the Arduino Uno has limited RAM, pointers are used to refer to string memory locations instead of duplicating strings:

```cpp
void displayMessage(const char* msg) {
  lcd.clear();
  lcd.print(msg);
}
```

This function will be called by other logic handling functions.


### Buzzer Control

Controlling the buzzer requires parameters such as the buzzer pin `BUZZER`, frequency `freq`, and duration `duration`, along with functional parameters like `repeat` and `interval`. Here is the relevant function:

We define `buzzerController()` for handling the buzzer, passing in frequency, duration, number of repeats, and interval. During debugging, the parameters are printed to the console to verify that they are being passed correctly:

```cpp
void buzzerController(int freq, int duration, int repeat, int interval) {
  Serial.println("Start Buzzing");
  Serial.print("Frequency: "); Serial.println(freq);
  Serial.print("Duration: "); Serial.println(duration);
  Serial.print("Repeat: "); Serial.println(repeat);
  Serial.print("Interval: "); Serial.println(interval);
  ...
```

In the case of the yellow and green LEDs, the buzzer will buzz repeatedly, controlled by a `for` loop with the interval set accordingly. After the loop completes, the buzzer is turned off by calling `buzzerOff()`:

```cpp
  for (int i = 0; i < repeat; i++) {
    tone(BUZZER, freq, duration);
    delay(interval);
  }
  buzzerOff();
}
```

If multiple buzzers need to work together in the future, it would be beneficial to control the pin numbers with variables to make the code more maintainable.

---

### LED Control

This section is similar to the buzzer control. In addition to the necessary parameters such as the LED pin `ledPin` and the output state `state`, functional parameters like the LCD display message `msg`, repeat count `repeat`, and interval `interval` are included. Here’s an explanation:

The `ledControl()` function handles the output of the LEDs. It is implemented similarly to `buzzerOff()` to facilitate future expansion of control features:

```cpp
void ledControl(int ledPin, bool state) {
  digitalWrite(ledPin, state ? HIGH : LOW);
}
```

Next, in the `ledController()` function, we handle the coordinated operation of the LED and related components when the LED is lit. Parameters include the LED pin, LCD display message, repeat count, and interval:

```cpp
void ledController(int ledPin, const char* msg, int repeat, int interval) {
  ...<1>
  ...<2>
  ...<3>
}
```

1. In step <1>, the LED is turned on, a message is displayed on the LCD, and the buzzer is controlled:
    
    ```cpp
      ledControl(ledPin, true);
      displayMessage(msg);
    ```

2. In step <2>, we print the current information for debugging purposes:
  
    ```cpp
      Serial.println("Start Lightening");
      Serial.print("LED Pin: "); Serial.println(ledPin);
      Serial.print("Repeat: "); Serial.println(repeat);
      Serial.print("Interval: "); Serial.println(interval);
    ```

3. In step <3>, the input parameters are processed. There are three cases: when both repeat and interval are greater than zero (for input `G` or `Y`), continuous output (for input `R`, set to -1), and out-of-domain cases. The corresponding code is as follows:

    ```cpp
      if (repeat > 0 && interval > 0) {
        buzzerController(BUZZER_FREQ, BUZZER_DURATION, repeat, interval);
      } else if (repeat == -1) {
        keepBuzzing = true;
      } else {
        Serial.println("Invalid parameter(s) received.");
      }
    ```

### Input Handling

This section regulates the aforementioned processes. After initialization, input text is processed with a `switch-case` statement to execute the corresponding functions, as shown below:

```cpp
void inputHandler(char input) {
  ...<1>
  ...<2>
}
```

1. In step <1>, initialization occurs to avoid potential exceptions caused by the buzzer, LED, or LCD not shutting down properly. The input is also converted to uppercase:

    ```cpp
      resetOutputs();
      input = toupper(input);
    ```

2. In step <2>, the input is processed, with corresponding parameters set and handled. Although this program is relatively simple, the routing logic will be useful when the program’s control logic becomes more complex:

    ```cpp
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
    ```

You can observe how the parameters defined earlier are compared with those passed to the `ledController()` function to execute the respective functions. After the `ledController()` loop concludes, the `initialMessage()` function is called to update the LCD to display "Awaiting input..." so the user knows the system is in an operable state.


## Main Program

Lastly, we return to the core control logic:

### Setup Function

In the `setup()` function, we initialize the output pins, set the baud rate, and display a message on the LCD to inform the user that the system is in standby mode:

```cpp
void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Awaiting Input...");
}
```

### Loop Function

In the `loop()` function, we first monitor for serial input. When input is detected and processed, the `inputHandler()` function is called to perform the corresponding function. Specifically, when the red LED is called using input `R`, the

 `ledController()` function sets the continuous buzzer output by assigning `keepBuzzing = 1`. This allows the buzzer to keep outputting while the board continues to monitor other behavior, allowing further input to switch states:

```cpp
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
```

### Video Demostration

https://drive.google.com/file/d/154WCeubZRZMpK3TZCdryNwx0p4G5TwuM/view?usp=drive_link

## Conclusion

This project demonstrates the control of an Arduino system utilizing LEDs, an I2C LCD, and a buzzer. Through serial input, users can interact with the system, triggering different behaviors for each component. The system manages multiple functionalities such as turning on specific LEDs, controlling the buzzer with adjustable frequency, duration, and intervals, and displaying corresponding messages on the LCD. The project is designed with modular functions to facilitate easy expansion and maintenance, ensuring a smooth interaction between hardware components based on user inputs.
