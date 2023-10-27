const int redLEDPin = 11;
const int greenLEDPin = 10;
const int blueLEDPin = 9;

const int redSensorPin = A0;

int redValue = 0;
int redSensorValue = 0;

void setup() {
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redSensorPin, INPUT);
  Serial.begin(9600);

  // Set up Timer Interrupt
  noInterrupts(); // Disable interrupts
  TCCR1A = 0; // Clear TCCR1A register
  TCCR1B = 0; // Clear TCCR1B register
  TCNT1 = 0; // Clear timer count
  OCR1A = 15624; // Set compare match register (16MHz / (256 * 2Hz) - 1)
  TCCR1B |= (1 << WGM12); // Turn on CTC mode
  TCCR1B |= (1 << CS12); // Set prescaler to 256
  TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
  interrupts(); // Enable interrupts
}

ISR(TIMER1_COMPA_vect) {
  // Timer Interrupt Service Routine
  redSensorValue = analogRead(redSensorPin);
  Serial.print(redSensorValue);

  analogWrite(redLEDPin, 255);
  analogWrite(greenLEDPin, 255);
  analogWrite(blueLEDPin, 255);

  redValue = redSensorValue/4;

  Serial.print("Recalcualted Value \t Red:");
  Serial.print(redValue);

  analogWrite(redLEDPin, redValue);
}

void loop() {
  // Do nothing in the loop
}
