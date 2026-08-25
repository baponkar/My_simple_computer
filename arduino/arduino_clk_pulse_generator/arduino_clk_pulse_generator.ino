// Pin definitions
const int potPin = A0;       
const int clockPin = 13;     
const int modeSwitchPin = 2; // SPDT Toggle Switch for Auto/Manual
const int stepButtonPin = 3; // Push Button for Manual Step

// Timing variables for Auto Mode
unsigned long previousMicros = 0;
int clockState = LOW;
int lastMode = HIGH;

// Debounce variables for Manual Mode
int buttonState = HIGH;             
int lastButtonReading = HIGH;       
unsigned long lastDebounceTime = 0; 
const unsigned long debounceDelay = 50; // 50 milliseconds of debounce time

// NEW: Variable to track the clock count
unsigned long clockCount = 0; 

void setup() {
  pinMode(clockPin, OUTPUT);
  
  // INPUT_PULLUP uses Arduino's internal resistors.
  // This means the pins read HIGH when disconnected/open, 
  // and LOW when connected to Ground (closed/pressed).
  pinMode(modeSwitchPin, INPUT_PULLUP);
  pinMode(stepButtonPin, INPUT_PULLUP);

  // NEW: Start serial communication
  Serial.begin(9600);
}

void loop() {
  int currentMode = digitalRead(modeSwitchPin);

  // Clean up the clock line if we just flipped the mode switch
  if (currentMode != lastMode) {
    clockState = LOW;
    digitalWrite(clockPin, LOW);
    lastMode = currentMode;
  }

  if (currentMode == HIGH) {
    // ---------------- AUTO MODE ----------------
    int potValue = analogRead(potPin);
    // Map from 1 second (0.5 Hz) to 1 ms (500 Hz) half-periods
    unsigned long halfPeriod = map(potValue, 0, 1023, 1000000, 1000);
    unsigned long currentMicros = micros();

    if (currentMicros - previousMicros >= halfPeriod) {
      previousMicros = currentMicros;
      clockState = (clockState == LOW) ? HIGH : LOW;
      digitalWrite(clockPin, clockState);

      // NEW: Only increment and print when the clock pulses HIGH
      if (clockState == HIGH) {
        clockCount++;
        Serial.print("Clock tick: ");
        Serial.println(clockCount);
      }
    }
  } 
  else {
    // --------------- MANUAL MODE ---------------
    int currentReading = digitalRead(stepButtonPin);

    // Reset debounce timer if the button state just changed (contact bounce)
    if (currentReading != lastButtonReading) {
      lastDebounceTime = millis();
    }

    // Only register the state if it has been stable longer than the delay
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (currentReading != buttonState) {
        buttonState = currentReading;
        
        // Button is active LOW (because of INPUT_PULLUP)
        if (buttonState == LOW) {
          digitalWrite(clockPin, HIGH);
          
          // NEW: Increment and print on manual button press
          clockCount++;
          Serial.print("Clock tick: ");
          Serial.println(clockCount);
          
        } else {
          digitalWrite(clockPin, LOW);
        }
      }
    }
    lastButtonReading = currentReading;
  }
}
