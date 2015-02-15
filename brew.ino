//  BREWING THE INTERNET
//  hackcooper 2015

int led = D0; // You'll need to wire an LED to this one to see it blink.
int led2 = D7; // This one is the built-in tiny one to the right of the USB jack
int cups = 0; // placeholder for cup measurement amount
int brewing = 0; // status var for currently brewing
char publishString[64]; // placeholder for json output
unsigned long startTime = 0; // determine when to timeout

// turn the machine on or off
int changeState(String ip) {

    // turn the machine on
    if( digitalRead(led) == LOW ){
        digitalWrite(led, HIGH);
        digitalWrite(led2, HIGH);
        startTime = millis();
        brewing = 1;

        // measure & publish amount of cups to brew
        cups = measureCups();
        sprintf(publishString,"{\"Cups\": %d}",cups);
        Spark.publish("Cups",publishString);
        return 1;

    } else {
        // turn the machine off
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);
        brewing = 0;
        return 1;
    }

    // something FUNKY going on
    return 0;
}

// check how many cups about to brew
int measureCups() {

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

    int test = 0;
    int level = 0;

    // loop over pin five times, check noise
    for( int i = 0; i < 5; i++ ){
        if( digitalRead(pin) == LOW ) test++;
    }

    // only return high if you get 5/5 pos reads
    if( test > 4 ) level = 1;
    return level;

}

// check for timeout conditions,after 15 seconds
void checkTimeout() {
    unsigned long now = millis();
    if (now-startTime>15000UL) changeState("local");
}

void setup() {

    // spark core definitions
    Spark.function("swap", changeState);

    // pin mode definitions
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);
    pinMode(A6, INPUT_PULLUP);
    pinMode(A7, INPUT_PULLUP);

    // initial conditions
    digitalWrite(led, LOW);

}

void loop(){
    // check brew status for timeout
    if( brewing ) checkTimeout();
}


