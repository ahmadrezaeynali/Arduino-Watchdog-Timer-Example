/*
 * Example use of Arduino watchdog timer
 * 
 * This sketch is used in my video to explain how
 * the Arduino watchdog timer operates. 
 * Check the video at: https://youtu.be/PsAvMV9EIMc
 * 
 * Portions of the code are inspired and adapted from
 * the article by Big Dan the Blogging Man
 * https://bigdanzblog.wordpress.com/2014/10/24/arduino-watchdog-timer-wdt-example-code/
 */
#include <avr/wdt.h>

int i;
 
void setup(){
  //watchdog timer with 4 Seconds time out
  wdt_enable(WDTO_4S);

  pinMode(LED_BUILTIN, OUTPUT);
  
  // at bootup, flash LED 3 times quick so I know the reboot has occurred.
  for (i = 0; i < 3; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100L);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100L);
  }
  
  // delay a bit more so it is clear we are done with setup
  delay(1000L);
}
 
void loop() {
  // this loop simply turns the LED on and then waits i*250ms. As i increases, the amount of time
  // increases. Until finally the watch dog timer doesn't get reset quickly enough.
  for (i = 0; i < 10000; i++) {
    // at the top of this infinite loop, reset the watchdog timer
    wdt_reset();
    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(i*250L);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250L);
  }
}
