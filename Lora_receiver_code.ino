
/*
LoRa Module to Arduino:
VCC to 3.3V
GND to GND
NSS to Digital Pin 10
SCK to Digital Pin 13
MOSI to Digital Pin 11
MISO to Digital Pin 12
RST to Digital Pin 9
DIO0 to Digital Pin 2


*/
/*
LoRa Module to Arduino:
VCC to 3.3V
GND to GND
NSS to Digital Pin 10
SCK to Digital Pin 13
MOSI to Digital Pin 11
MISO to Digital Pin 12
RST to Digital Pin 9
DIO0 to Digital Pin 2


*/
#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  
  // Initialize LoRa module
  LoRa.setPins(10, 9, 2); // NSS, RST, DIO0
  if (!LoRa.begin(915E6)) { // Change to your region's frequency
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }
    Serial.print("Received: ");
    Serial.println(receivedData);
  }
}