/* Project Alarm Clock */
/* Designed by: Pavittar Singh (200238210)*/
/*              Sharandeep kaur Nagra (200235016)  */
/*              Parminder kaur Paneser(200241190)  */


#define vers = "1.01"
#define ledPin 13
#define secondPin 4
#define minutePin 5
#define hourPin 6
#define weekdayPin 7
#ifndef alarm_clock_h
#define alarm_clock_h
#include <WProgram.h>

#define Max_alarms 4


int second=0, minute=0, hour=0, weekday=1; // declare time variables
// these time variables are declared globally so they can be used ANYWHERE in your program


void setup() {

blinkLED(ledPin, 4, 100); // blink an LED at the start of the program, to show the code is running
Serial.begin(9600); // start up serial communications
pinMode(secondPin, INPUT); //pins for normally closed switches to set the time
pinMode(minutePin, INPUT);
pinMode(hourPin, INPUT);
pinMode(weekdayPin, INPUT);
digitalWrite(secondPin, HIGH); // writing an input high turns on pull-up resistors
digitalWrite(minutePin, HIGH);
digitalWrite(hourPin, HIGH);
digitalWrite(weekdayPin, HIGH);
}

void loop() {

static unsigned long lastTick = 0; // set up a local variable to hold the last time we moved forward one second
// (static variables are initialized once and keep their values between function calls)

// move forward one second every 1000 milliseconds
if (millis() - lastTick >= 1000) {
lastTick = millis();
serialOutput();
second++;
}

// move forward one minute every 60 seconds
if (second > 59) {
minute++;
second = 0; // reset seconds to zero
}

// move forward one hour every 60 minutes
if (minute > 59) {
hour++;
minute = 0; // reset minutes to zero
}

// move forward one weekday every 24 hours
if (hour > 23) {
weekday++;
hour = 0; // reset hours to zero
}

// reset weekdays on Saturday
if (weekday > 7) {
weekday = 1;
}

checkButtons(); // runs a function that checks the setting buttons
}

void checkButtons() {
static boolean secPressed=false, minPressed=false, hourPressed=false, wkdayPressed=false; //track button state

if (digitalRead (secondPin)==LOW && secPressed == false) { // if a normally closed switch is pressed
second++; // advance by one second
secPressed = true; // note the pressed state
}
if (digitalRead (secondPin)==HIGH) secPressed = false; // reset the state when the button is released

if (digitalRead (minutePin)==LOW && minPressed == false) {
minute++;
minPressed = true;
}
if (digitalRead (minutePin)==HIGH) minPressed = false;

if (digitalRead (hourPin)==LOW && hourPressed == false) {
hour++;
hourPressed = true;
}
if (digitalRead (hourPin)==HIGH) hourPressed = false;

if (digitalRead (weekdayPin)==LOW && wkdayPressed == false) {
weekday++;
secPressed = true;
if (digitalRead (weekdayPin)==HIGH) wkdayPressed = false;
}
}

void printWeekday (int dayNum) {
// print a weekday, based on the day number
switch (dayNum) {
case 1:
Serial.print ("Sunday");
break;
case 2:
Serial.print ("Monday");
break;
case 3:
Serial.print ("Tuesday");
break;
case 4:
Serial.print ("Wednesday");
break;
case 5:
Serial.print ("Thursday");
break;
case 6:
Serial.print ("Friday");
break;
case 7:
Serial.print ("Saturday");
break;
}
}

void serialOutput() {
// this function creates a clock you can read through the serial port
// your clock project will have a MUCH more interesting way of displaying the time
// get creative!
printWeekday(weekday); // picks the right word to print for the weekday
Serial.print(", "); // a comma after the weekday
Serial.print(hour, DEC); // the hour, sent to the screen in decimal format
Serial.print(":"); // a colon between the hour and the minute
Serial.print(minute, DEC); // the minute, sent to the screen in decimal format
Serial.print(":"); // a colon between the minute and the second
Serial.println(second, DEC); // the second, sent to the screen in decimal format
}

// this utility function blinks the an LED light as many times as requested
void blinkLED(byte targetPin, int numBlinks, int blinkRate) {
for (int i=0; i < numBlinks; i++) {
digitalWrite(targetPin, HIGH); // sets the LED on
delay(blinkRate); // waits for a blinkRate milliseconds
digitalWrite(targetPin, LOW); // sets the LED off
delay(blinkRate);
}
}

class alarm_clock
{
public:
  alarm_clock(boolean noo);
  byte run(); // Returns which alarm is triggered, 0-Max_alarms, 255 means no alarm is triggered.
  byte set_alarm(byte alarm_num, byte hr, byte mnt, byte dow); // Returns 255 if parameters are invalid. Returns 0 if valid.
  void turn_on(byte alarm_num);
  void turn_off(byte alarm_num);
  void alarm();
  boolean within(byte a, byte dow);
  
  typedef struct {
  byte hr;
  byte mnt;
  byte dow;
  boolean on_off; // This variable is not used. Instead dow is used to turn the alarm off or on.
  } entry;

  entry alarms[Max_alarms];
  boolean alarm_is_on; // Alarm is on. alarm() will be called if this is true.
  byte snooze;
};
#endif


 
