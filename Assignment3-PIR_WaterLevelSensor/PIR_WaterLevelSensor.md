## Criteria

**Application Design Using PIR Sensor, Water Level Sensor, Buzzer, and LCD:**

1. **Initial State**: The LCD displays no content.
2. **Detection of Presence**: 
   - If someone is detected, the LCD displays “People” on the second line.
   - If no one is detected, it displays “Nobody” on the second line.
3. **Operations When Someone is Present**:
   - **High Water Level**: When the water level in the container exceeds a set threshold, activate the buzzer to emit a continuous sound, and display “Urgent” on the first line of the LCD.
   - **Low Water Level**: When the water level falls below the threshold, deactivate the buzzer (no sound), and change the first line of the LCD to display “Safety.”

# Preparation

## 1. Hardware Wiring Diagram

![Circuit Diagram corresponding to this program](https://raw.githubusercontent.com/csning1998/Arduino-Assignments/refs/heads/main/Assignment3-PIR_WaterLevelSensor/PIR_WaterLevelSensor.png "Circuit Diagram corresponding to this program")

Reference: https://www.tinkercad.com/things/6jEiMD0Uive-assignment3-pirwaterlevelseneor

---

## 2. Code

### A. Pre-Setup

#### **Importing Libraries**

In this assignment, we need to implement I2C control for the LCD. Therefore, we import necessary libraries, including one for controlling the I2C communication protocol with the LCD. We also initialize the LCD, specifying the I2C address as 0x27, and set the LCD size to 2 rows and 16 columns as shown below:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
```

#### **Variable Declaration**

We begin by defining control variables for each component. The PIR sensor (`pirPin`) and the buzzer (`buzzerPin`) use digital pins, while the water level sensor (`waterSensorPin`) uses an analog pin. The goal is to activate the buzzer if the water level exceeds a defined threshold (`waterThreshold`), which we set to 500 in this case.

When the sensor is dry, environmental noise may cause minor fluctuations, with a net value usually between 20 and 35. To filter out these small signals, we set a noise threshold (`noiseThreshold`). We also define a baseline as an initial parameter to account for initial reading errors of the water level sensor in air, which will be processed using conditional statements later.

```cpp
const int pirPin = 2;
const int buzzerPin = 3;
const int waterSensorPin = A0;
const int waterThreshold = 500;
const int noiseThreshold = 50;
int baseline = 0;
```

### B. Main Program

#### **void setup()**

In this function, we perform initializations. Using a `for` loop, we calculate the baseline value by taking the average of 10 consecutive readings from the water sensor:

```cpp
void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    noTone(buzzerPin);

    pinMode(pirPin, INPUT);
    pinMode(buzzerPin, OUTPUT);

    for (int i = 0; i < 10; i++) {
        baseline += analogRead(waterSensorPin);
        delay(10);
    }
    baseline /= 10;
}
```

#### **void loop()**

Given the simplicity of this assignment, we write the main code within `loop()` without using additional functions.

```cpp
void loop() {
    ...<1>
    ...<2>
    ...<3>
}
```

##### (a) Regarding <1>:

We use `pirState` to check if there is someone present, implementing it as a Boolean function. The `waterLevel` variable is the reading from `analogRead(waterSensorPin)`, with the baseline subtracted.

Next, we compare `waterLevel` with the environmental noise threshold (`noiseThreshold`). If it is below this threshold, we set `waterLevel` to zero.

```cpp
int pirState = digitalRead(pirPin);
int waterLevel = analogRead(waterSensorPin) - baseline;

if (waterLevel < noiseThreshold) {
    waterLevel = 0;
}
```

##### (b) Regarding <2>: Human and Water Level Status Check

This is the main conditional logic of the assignment: if a person is detected, the LCD displays "People" on the second row; otherwise, it displays "Nobody" and turns off the buzzer. When a person is detected, we then check the water level threshold as described in part <a> below.

```cpp
if (pirState == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("People             ");
} else {
    lcd.setCursor(0, 1);
    lcd.print("Nobody             ");
    lcd.setCursor(0, 0);
    lcd.print("                         ");
    digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin);
}
```

In part <a>, if the `waterLevel` exceeds `waterThreshold`, the LCD displays "Urgent" on the first row and activates the buzzer. If it is below the threshold, it displays "Safety" and turns off the buzzer:

```cpp
if (waterLevel > waterThreshold) {
    lcd.setCursor(0, 0);
    lcd.print("Urgent             ");
    tone(buzzerPin, 500);
} else {
    lcd.setCursor(0, 0);
    lcd.print("Safety             ");
    noTone(buzzerPin);
}
```

##### (c) Debug Area

To verify the code's functionality, we print the states of the PIR sensor and water level sensor here:

```cpp
Serial.print("PIR State: ");
Serial.print(pirState == HIGH ? "People" : "Nobody");
Serial.print(" | Water Level: ");
Serial.println(waterLevel);

delay(100);
```

---

### **Video Demonstration**

[Google Drive File](https://drive.google.com/file/d/19VX85R9rNvwCxk4UI6X50ZavkKxuMKIT/view?usp=sharing)
