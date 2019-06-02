/*
   RadioLib CC1101 Transmit Example

   This example transmits packets using CC1101 FSK radio module.
   Each packet contains up to 64 bytes of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>

// CC1101 has the following connections:
// NSS pin:   10
// GDO0 pin:  2
// GDO2 pin:  3
CC1101 cc = new Module(10, 2, 3);

// or using RadioShield
// https://github.com/jgromes/RadioShield
//CC1101 cc = RadioShield.ModuleA;

void setup() {
  Serial.begin(9600);

  // initialize CC1101
  Serial.print(F("[CC1101] Initializing ... "));
  // carrier frequency:                   868.0 MHz
  // bit rate:                            4.8 kbps
  // Rx bandwidth:                        325.0 kHz
  // frequency deviation:                 48.0 kHz
  // sync word:                           0xD391
  int state = cc.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  Serial.print(F("[CC1101] Transmitting packet ... "));

  // you can transmit C-string or Arduino string up to 63 characters long
  int state = cc.transmit("Hello World!");

  // you can also transmit byte array up to 63 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    int state = cc.transmit(byteArr, 8);
  */

  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F(" success!"));

  } else if (state == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 255 bytes
    Serial.println(F(" too long!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }

  // wait for a second before transmitting again
  delay(1000);
}
