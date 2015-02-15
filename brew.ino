//  BREWING THE INTERNET
//  hackcooper 2015

int led = D0; // You'll need to wire an LED to this one to see it blink.
int led2 = D7; // This one is the built-in tiny one to the right of the USB jack
int cups = 0; // placeholder for cup measurement amount
int brewing = 0; // status var for currently brewing
int shuttingDown = 0; // status for cleaning out water bin
char publishString[64]; // placeholder for json output
unsigned long tempTime = 0; // determine when to check if full
unsigned long finishTime = 0; // determine when to timeout
unsigned long startTime = 0; // determine when to timeout
unsigned long lcdTime = 0; // determine when to swap LCD text
int lcdStatus = 0; // holds which LCD screen status to display

// turn the machine on or off
int changeState(String ip) {

    // turn the machine on
    if( digitalRead(led) == LOW ){
        digitalWrite(led, HIGH);
        digitalWrite(led2, HIGH);
        tempTime = millis();
        finishTime = 0;
        brewing = 1;
        displayBrewing();

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
    if( test > 4 ) level = 2;
    return level;

}

// check for timeout conditions,after 15 seconds
void checkTimeout() {

    // get the current time
    unsigned long now = millis();

    // only perform the check every 10s
    if( now-tempTime>10000UL ){
        // if cups are empty, countdown timer
        if ( measureCups() == 0 && !shuttingDown ) {
            finishTime = millis();
            shuttingDown = 1;
        }
    }

    // wait 30 seconds after finishing brewing
    if( now-finishTime>30000UL && shuttingDown ){
        sprintf(publishString,"{\"BrewStatus\": \"done\"}",cups);
        Spark.publish("BrewDone",publishString);
        changeState("local");
        shuttingDown = 0;
    }

}

// LCD Functions:
// check for timeout conditions for LCD
void checkLCDTimeout() {
    unsigned long now = millis();
    if (now-lcdTime>5000UL && lcdStatus == 0){
        lcdStatus = 1;
        displayCups();
    }
    else if (now-lcdTime>5000UL && lcdStatus == 1){
        lcdStatus = 2;
        displaySlogan();
    }
    else if (now-lcdTime>5000UL && lcdStatus == 2){
        lcdStatus = 0;
        displayWelcome();
    }
}

void selectLineOne(){  //puts the cursor at line 0 char 0.
   Serial.write(0xFE); //command flag
   Serial.write(128);  //position
   delay(40);
}
void selectLineTwo(){  //puts the cursor at line 0 char 0.
   Serial.write(0xFE); //command flag
   Serial.write(192);  //position
   delay(40);
}

// display Mr. Coffi welcome message on LCD - status=0
void displayWelcome(){
    Serial1.write(0xFE); // command flag
    Serial1.write(0x01); // clear display
    selectLineOne();
    Serial1.write(" Welcome to the");
    Serial1.write("        Mr.Cof-Fi!");
    lcdTime = millis();
}

// read number of cups in tnak and display on LCD - status=1
void displayCups(){
    Serial1.write(0xFE); // command flag
    Serial1.write(0x01); // clear display
    selectLineOne();
    Serial1.write("Cups in tank: ");
    Serial1.print(measureCups(), HEX);
    lcdTime = millis();
}

// display slogan on LCD - status=2
void displaySlogan(){
    Serial1.write(0xFE); // command flag
    Serial1.write(0x01); // clear display
    selectLineOne();
    Serial1.write("     Yo for");
    selectLineTwo();
    Serial1.write("             some jo!");
    lcdTime = millis();
}

// display brewing on LCD until done brewing
void displayBrewing(){
    Serial1.write(0xFE); // command flag
    Serial1.write(0x01); // clear display
    selectLineOne();
    Serial1.write("Brewing...");
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

    // Serial LCD setup
    Serial1.begin(9600);
    delay(20);
    displayWelcome();
}

void loop(){
    // check brew status for timeout
    if( brewing ) checkTimeout();
    else checkLCDTimeout();
}


