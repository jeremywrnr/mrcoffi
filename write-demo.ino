// Define the pins we're going to call pinMode on

// You'll need to wire an LED to this one to see it blink.
int led = D0;

// This one is the built-in tiny one to the right of the USB jack
int led2 = D7;

// This routine runs only once upon reset
void setup() {
  // Initialize D0 + D7 pin as output
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code.
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop() {
  digitalWrite(led, HIGH);   // Turn ON the LED pins
  digitalWrite(led2, HIGH);
  delay(500);               // Wait for 1000mS = 1 second
  digitalWrite(led, LOW);    // Turn OFF the LED pins
  digitalWrite(led2, LOW);
  delay(500);               // Wait for 1 second in off mode
}
