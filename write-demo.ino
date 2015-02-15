
int led = D0; // You'll need to wire an LED to this one to see it blink.
int led2 = D7; // This one is the built-in tiny one to the right of the USB jack

int changeState(String ip) {
    if( digitalRead(led) == HIGH ){
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);
    } else {
        digitalWrite(led, HIGH);
        digitalWrite(led2, HIGH);
    }
    return 1;
}

int measureCups(String ip) {
    return 1;
}

int cups = 1;

void setup() {
    Spark.function("swap", changeState);
    Spark.variable("cups", &cups, INT);
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    digitalWrite(led, HIGH);
}

void loop() { }

