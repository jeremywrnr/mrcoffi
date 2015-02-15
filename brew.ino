//  BREWING THE INTERNET
//  hackcooper 2015

int led = D0; // You'll need to wire an LED to this one to see it blink.
int led2 = D7; // This one is the built-in tiny one to the right of the USB jack
int cups = 0; // placeholder for cup amounts

// turn the machine on or off
int changeState(String ip) {

    // turn the machine off
    if( digitalRead(led) == LOW ){
        digitalWrite(led, HIGH);
        digitalWrite(led2, HIGH);
    } else {
        // turn the machine on
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);
    }
    return 1;
}


// check how many cups about to brew
int measureCups(String ip) {

    // reset the cup amt.
    cups = 0;

    // check and sum all levels
    for (int pin = A0; pin <= A7; ++pin) {
        digitalRead(A0) && cups++;
    }

    return cups;

}

void setup() {

    // spark core definitions
    Spark.function("swap", changeState);
    Spark.function("mcups", measureCups);
    Spark.variable("cups", &cups, INT);

    // pin mode definitions
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    for (int pin = A0; pin <= A7; ++pin) {
        pinMode(pin, INPUT);
    }

    // initial conditions
    digitalWrite(led, HIGH);
}

void loop(){}
