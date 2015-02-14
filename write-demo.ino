int led = D0; // You'll need to wire an LED to this one to see it blink.
int led2 = D7; // This one is the built-in tiny one to the right of the USB jack

void swapLed();

void setup() {
    Spark.function("swap", swapLed);
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
}

void loop() { }

void swapLed() {
    if( digitalRead(led) == HIGH ){
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);
    } else {
        digitalWrite(led, HIGH);
        digitalWrite(led2, HIGH);
    }
}
