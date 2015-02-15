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

    // reset cups
    cups = 0;

    // check and sum all levels
    cups += checkFloater(A0);
    cups += checkFloater(A1);
    cups += checkFloater(A2);
    cups += checkFloater(A3);
    cups += checkFloater(A4);
    cups += checkFloater(A5);
    cups += checkFloater(A6);
    cups += checkFloater(A7);

    // return the amount of cups
    return cups;

}

// check variance of polling
int checkFloater(int pin) {

    int hi = 0;
    int lo = 0;
    int level = 0;

    for( int i = 10; i; i++ ){
        if( digitalRead(pin) == LOW ){
            lo++;
        } else {
            hi++;
        }
    }

    // only return high if you get at least 8 high polls
    if( hi > 8 ) level++;
    return level;

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

