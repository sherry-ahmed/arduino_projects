/*
GPS Module to Arduino:
VCC to 5V
GND to GND
TX to Digital Pin 4
RX to Digital Pin 3
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
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Example frequency settings
//#define LORA_BAND 915E6  // US915 (adjust according to your region)

// Uncomment the correct frequency for your region
//#define LORA_BAND 868E6  // EU868
//#define LORA_BAND 915E6  // US915, AU915
//#define LORA_BAND 923E6  // AS923
//#define LORA_BAND 865E6  // IN865

TinyGPSPlus gps;
SoftwareSerial gpsSerial(3, 4); // RX, TX for GPS

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  
  // Initialize LoRa module
  LoRa.setPins(10, 9, 2); // NSS, RST, DIO0
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
  
  //if (gps.location.isUpdated()) {
    // Print latitude and longitude to Serial Monitor
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6); // Print latitude with 6 decimal places
    Serial.print(", Longitude: ");
    Serial.println(gps.location.lng(), 6); // Print longitude with 6 decimal places
    
    // Prepare data to send via LoRa
    String gpsData = "";
    gpsData += "Lat: ";
    gpsData += gps.location.lat();
    gpsData += ", Lon: ";
    gpsData += gps.location.lng();
    
    Serial.print("Sending: ");
    Serial.println(gpsData);
    
    // Send data via LoRa
    LoRa.beginPacket();
    LoRa.print(gpsData);
    LoRa.endPacket();
    
    delay(100); // Send data every second
  //}
}
