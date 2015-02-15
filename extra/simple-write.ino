int led = D0; // You'll need to wire an LED to this one to see it blink.
int led2 = D7; // This one is the built-in tiny one to the right of the USB jack

void setup() {
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
}

void loop() {
    delay(500);
    if( digitalRead(led) == HIGH ){
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);
    } else {
        digitalWrite(led, HIGH);
        digitalWrite(led2, HIGH);
    }
}
