//  BREWING THE INTERNET
//  hackcooper 2015

int mrcf = D0; // the pin hooked up to the mr coffee heater relay
int led2 = D7; // the built-in tiny one to the right of the USB jack
int cups = 0; // placeholder for cup measurement amount
int brewing = 0; // status var for currently brewing
int lcd_status = 0; // holds which LCD screen status to display
int shutting_down = 0; // status for cleaning out water bin
char publish_string[64]; // placeholder for json output
unsigned long lcd_time = 0; // determine when to swap LCD text
unsigned long temp_time = 0; // determine when to check if full
unsigned long start_time = 0; // determine when to timeout
unsigned long finish_time = 0; // determine when to timeout

// turn the machine on
void power_on() {
    brewing = 1;
    digitalWrite(mrcf, HIGH);
    digitalWrite(led2, HIGH);
}

// turn the machine off
void power_off() {
    brewing = 0;
    digitalWrite(mrcf, LOW);
    digitalWrite(led2, LOW);
}

int brew(String ip) {

    // turn the machine on
    if( !brewing ){
        temp_time = millis();
        finish_time = 0;
        display_brewing();
        power_on();

        // measure & publish amount of cups to brew
        cups = measure_cups();
        sprintf(publish_string,"{'Cups': %d, 'IP': %s}",cups,ip);
        Spark.publish("Cups",publish_string);
        return 1;
    }

    // something FUNKY going on
    return 0;

}

// check how many cups about to brew
int measure_cups() {

    // reset cups
    cups = 0;

    // check and sum all levels
    cups += check_level(A0);
    cups += check_level(A1);
    cups += check_level(A2);
    cups += check_level(A3);
    cups += check_level(A4);
    cups += check_level(A5);
    cups += check_level(A6);
    cups += check_level(A7);

    // return the amount of cups
    return cups;

}

// check variance of polling
int check_level(int pin) {

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
void check_time() {

    // get the current time
    unsigned long now = millis();

    // (check every 10s) & cups are empty, start countdown timer
    if( now-temp_time>10000UL && measure_cups() == 0 && !shutting_down ) {
        finish_time = millis();
        shutting_down = 1;
    }

    // wait 300 seconds after finishing brewing
    if( now-finish_time>300000UL && shutting_down ){
        power_off(); // actually turn off machine
        sprintf(publish_string,"{\"Brew_status\": \"done\"}",cups);
        Spark.publish("Brew_done",publish_string);
        shutting_down = 0;
    }

}

// LCD Functions:
// check for timeout conditions for LCD
void check_lcd() {
    unsigned long now = millis();
    if (now-lcd_time>5000UL && lcd_status == 0){
        lcd_status = 1;
        display_cups();
    } else if (now-lcd_time>5000UL && lcd_status == 1){
        lcd_status = 2;
        display_slogan();
    } else if (now-lcd_time>5000UL && lcd_status == 2){
        lcd_status = 0;
        display_welcome();
    }
}

void select_line_one(){  //puts the cursor at line 0 char 0.
    Serial.write(0xFE); //command flag
    Serial.write(128);  //position
    delay(40);
}

void select_line_two(){  //puts the cursor at line 1 char 0.
    Serial.write(0xFE); //command flag
    Serial.write(192);  //position
    delay(40);
}

void prepare_serial(){
    Serial1.write(0xFE); // command flag
    Serial1.write(0x01); // clear display
    select_line_one();    // call above method
}

// display Mr. Coffi welcome message on LCD - status=0
void display_welcome(){
    prepare_serial();
    Serial1.write(" Welcome to the");
    Serial1.write("        Mr.Cof-Fi!");
    lcd_time = millis();
}

// read number of cups in tank and display on LCD - status=1
void display_cups(){
    prepare_serial();
    Serial1.write("Cups in tank: ");
    Serial1.print(measure_cups(), HEX);
    lcd_time = millis();
}

// display slogan on LCD - status=2
void display_slogan(){
    prepare_serial();
    Serial1.write("     Yo for");
    select_line_two();
    Serial1.write("             some jo!");
    lcd_time = millis();
}

// display brewing on LCD until done brewing
void display_brewing(){
    prepare_serial();
    Serial1.write("Brewing...");
    select_line_two();
    Serial1.write("             some jo!");
}

void setup() {

    // spark core definitions
    Spark.function("brew", brew);

    // pin mode definitions
    pinMode(mrcf, OUTPUT);
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
    digitalWrite(mrcf, LOW);

    // Serial LCD setup
    Serial1.begin(9600);
    delay(20);
    display_welcome();

}

void loop(){
    // check brew status for timeout
    if( brewing ) check_time();
    else check_lcd();
}
