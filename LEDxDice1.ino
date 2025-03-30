// Define the digital pins for the LEDs
int first = 2;
int second = 3;
int third = 4;
int fourth = 5;
int fifth = 6;
int sixth = 7;

// Pin for the button switch
int button = 12;
// Variable to check the state of the button switch
int pressed = 0;

void setup() {
  // Set all LED pins to OUTPUT
  for (int i = first; i <= sixth; i++) {
    pinMode(i, OUTPUT);
  }
  // Set button pin to INPUT
  pinMode(button, INPUT);
  
  // Initialize random seed using noise from analog pin 0 (should be unconnected)
  randomSeed(analogRead(0));

  // Initialize serial communication for debugging (optional)
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
}

void buildUpTension() {
  // Light LEDs from left to right and back to build up tension
  // Left to right
  for (int i = first; i <= sixth; i++) {
    digitalWrite(i, HIGH); // Turn on the current LED
    delay(100); // Wait for a moment
    if (i != first) {
      digitalWrite(i - 1, LOW); // Turn off the previous LED
    }
  }
  // Right to left
  for (int i = sixth; i >= first; i--) {
    digitalWrite(i, HIGH); // Turn on the current LED
    delay(100); // Wait for a moment
    if (i != sixth) {
      digitalWrite(i + 1, LOW); // Turn off the next LED
    }
  }
}

void showNumber(int number) {
  // Turn on LEDs based on the rolled number
  digitalWrite(first, HIGH); // Always turn on the first LED
  if (number >= 2) {
    digitalWrite(second, HIGH);
  }
  if (number >= 3) {
    digitalWrite(third, HIGH);    
  }
  if (number >= 4) {
    digitalWrite(fourth, HIGH);    
  }
  if (number >= 5) {
    digitalWrite(fifth, HIGH);    
  }
  if (number == 6) {
    digitalWrite(sixth, HIGH);    
  }
}

int throwDice() {
  // Get a random number in the range [1,6]
  int randNumber = random(1, 7);
  
  #ifdef DEBUG
    Serial.println(randNumber); // Print the random number for debugging
  #endif
  
  return randNumber;
}

void setAllLEDs(int value) {
  // Set all LEDs to the specified value (HIGH or LOW)
  for (int i = first; i <= sixth; i++) {
    digitalWrite(i, value);
  }
}

void loop() {
  // Check if the button is pressed to throw the dice
  pressed = digitalRead(button);

  if (pressed == HIGH) {
    // Remove previous number by turning off all LEDs
    setAllLEDs(LOW);
    
    // Build up tension before showing the result
    buildUpTension();
    
    // Throw the dice and get the result
    int thrownNumber = throwDice();
    
    // Show the rolled number
    showNumber(thrownNumber);
    
    // Optional: Turn off LEDs after a short delay
    delay(2000); // Keep the result displayed for 2 seconds
    setAllLEDs(LOW); // Turn off all LEDs after displaying the number
  } 
}