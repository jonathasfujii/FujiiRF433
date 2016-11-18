/*
 
 */

#define MY_DEBUG
#include <RF433.h>

// RF433
#define RFTX_PIN 2
#define RFRX_PIN 3

RF433 rf433(RFRX_PIN, RFTX_PIN);

void setup()
{
  #ifdef MY_DEBUG
  Serial.begin(9600);
  #endif
  // Make sure relays are off when starting up
}


void loop()
{ 
  long codigo = 182113845;
  rf433.enviarCodigo(codigo);
  Serial.println(codigo);
  delay(5000);  
}

