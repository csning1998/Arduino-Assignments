const int ledPins[] = {2, 3, 4, 5, 6};
const int redLedPins[] = {2, 4, 6};
const int greenLedPins[] = {3, 5};
const int numLeds = 5;
const int seqLength = 10;
const int seq[] = {0, 1, 2, 3, 4, 0, 2, 4, 1, 3};

bool runSeq = true;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (runSeq) {

    ledControlHandler(ledPins, numLeds, LOW);    
    
    // Verse 1: LED Sequentially Blinking
    for (int i = 0; i < seqLength; i++) {
      int ledIndexArray[] = { ledPins[seq[i]] };
      ledControlHandler(ledIndexArray, 1, HIGH);
      delay(1000);
      ledControlHandler(ledIndexArray, 1, LOW);
    }

    // Verse 2: Turning all Greed's off and Red's on 
    ledControlHandler(greenLedPins, 2, LOW);
    ledControlHandler(redLedPins, 3, HIGH);
    delay(1000);

    // Verse 3: Turning all Red's off and Greed's on 
    ledControlHandler(redLedPins, 3, LOW); 
    ledControlHandler(greenLedPins, 2, HIGH);
    delay(1000);

    // Verse 4: Turning on all LEDs
    ledControlHandler(ledPins, numLeds, HIGH);
    delay(1000);

    // Verse 5: Turning off all LEDs
    ledControlHandler(ledPins, numLeds, LOW);
    delay(1000);
  }

  // Built-in LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

// LED Control Handler
void ledControlHandler(const int ledArray[], int arraySize, int state) {
  for (int i = 0; i < arraySize; i++) {
    digitalWrite(ledArray[i], state);
  }
}
