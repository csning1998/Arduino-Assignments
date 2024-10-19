int buzzerPin = 8;

#define NOTE_E4  330
#define NOTE_DS4 311
#define NOTE_B4  494
#define NOTE_D4  294
#define NOTE_C4  262
#define NOTE_A3  220
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_A4  440
#define NOTE_B3  247
#define NOTE_GS4 415
#define NOTE_DS5 622

int melody[] = {
  NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_B4, NOTE_D4, NOTE_C4, NOTE_A3,
  NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4,
  NOTE_E4, NOTE_GS4, NOTE_B4, NOTE_C5,
  NOTE_E4, NOTE_E5, NOTE_DS4, NOTE_DS5, NOTE_D4, NOTE_B4
};

int noteDurations[] = {
  200, 200, 200, 200, 200, 200, 200, 200, 400,
  200, 200, 200, 400,
  200, 200, 200, 400,
  200, 200, 200, 400, 200, 400
};

int medodySize = (sizeof(noteDurations) / sizeof(noteDurations[0]));

void setup() {
  for (int i = 0; i < medodySize; i++) {
    int noteDuration = noteDurations[i];
    tone(buzzerPin, melody[i], noteDuration);
    delay(noteDuration * 1.30);
    noTone(buzzerPin);
  }
}

void loop() {
  
}
