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
        cups = measureCups('ip');
    } else {
        // turn the machine on
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);
    }
    return 1;
}

// check how many cups about to brew
int measureCups(String ip) {

    // reset cups
    cups = 0;

    // check and sum all levels
    if( digitalRead(A0) == HIGH ) cups++;
    if( digitalRead(A1) == HIGH ) cups++;
    if( digitalRead(A2) == HIGH ) cups++;
    if( digitalRead(A3) == HIGH ) cups++;
    if( digitalRead(A4) == HIGH ) cups++;
    if( digitalRead(A5) == HIGH ) cups++;
    if( digitalRead(A6) == HIGH ) cups++;
    if( digitalRead(A7) == HIGH ) cups++;

    // return the amount of cups
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
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);

    // initial conditions
    digitalWrite(led, HIGH);
}

void loop(){}

