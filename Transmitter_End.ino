//Transmitter Arduino Nano
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
#include <SPI.h> 
#include "DHT.h";

// Define Constants
#define DHTPIN 7 // DHT-22 Output Pin connection
#define DHTTYPE DHT22 // DHT Type is DHT 22 (AM2302)
#define RELAY1 4 //BULB IS CONNECTED TO PIN 4
#define RELAY2 5 // DC FAN IS CONNECTED TO PIN 5

// Define Variables
float Hum; // Stores humidity value in percent
float Temp; // Stores temperature value in Celcius

// Define output strings
string str_humid;
string str_temp;
string str_out;

// Create Amplitude Shift Keying Object
RH_ASK project_driver;
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);


void setup() {
pinMode(RELAY1, OUTPUT); // set relay pin as output
pinMode(RELAY2, OUTPUT); // set relay pin as output
 // Initialize ASK Object
 project_driver.init();
 // Start DHT Sensor
 dht.begin(); 
}
void loop()

{
 delay(2000); // Delay so the DHT-22 sensor can stabalize 
  Temp = dht.readTemperature(); // Get Temperature value 
  Hum = dht.readHumidity(); // Get Humidity value
  if (Temp > 27){
   digitalWrite (RELAY2, LOW); // activate relay to turn ON FAN 
   digitalWrite (RELAY1, HIGH); // keep the bulb OFF
  }
  else if (Temp < 27){
  digitalWrite (RELAY1, LOW); //Activate to turn on the Bulb
  digitalWrite (RELAY2, HIGH); // keep the Fan OFF
  }
  else {
  digitalWrite (RELAY1, HIGH);/*keep both components OFF*/
  digitalWrite (RELAY2, HIGH);
  }


  // Convert Humidity to string
  str_humid = string(Hum);
 

  // Convert Temperature to string
  str_temp = string(Temp);
 // Combine Humidity and Temperature
  str_out = str_humid + "," + str_temp;
 
  // Compose output character
  static char *msg = str_out.c_str();
 
  project_driver.send((uint8_t *)msg, strlen(msg));
  project_driver.waitPacketSent();
}
