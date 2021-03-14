#include "SBUS.h"

#define CHANNELS 16

SBUS x8r(Serial1); // D18 -> RXD Inverted SBUS

uint16_t channels[CHANNELS];

bool failSafe = 0;
bool lostFrame = 0;

void setup() {
  Serial.begin( 57600 );
  // Serial.println("[Searial] is ready");

  // Serial.println("[SBUS] begin");
  x8r.begin();
  // Serial.println("[SBUS] end");

  // Serial.println("done.");
}

void loop() {

  // look for a good SBUS packet from the receiver
  if(x8r.read(&channels[0], &failSafe, &lostFrame)){

    if( failSafe || lostFrame ){
      delay( 100 );
      return;
    }

    Serial.println(" ------------------------------------------------ ");

    uint8_t chi = 0;
    // for(;chi < 4; chi++){
    for(;chi < CHANNELS; chi++){
      Serial.print(" chi: "); 
      Serial.print( chi );
      Serial.print(" val: ");
      Serial.print( channels[ chi ] );
      Serial.println("");
      // Serial.print("chi-"); Serial.print( chi );
      // Serial.print(" ");
      // Serial.print( channels[ chi ] );
      // Serial.print(" ");
    }

    Serial.println("");
    delay( 500 );

    // write the SBUS packet to an SBUS compatible servo
    // x8r.write(&channels[0]);
  }

}
