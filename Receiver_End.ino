//Receiver Arduino Uno
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
#include <SPI.h> 
#include <LiquidCrystal.h>
// Define output strings
string str_humid;
string str_temp;
string str_out;
LiquidCrystal display(12, 10, 5, 4, 3, 2);

// Create Amplitude Shift Keying Object
RH_ASK project_driver;
void setup()
{
  display.begin(16, 2);
  // Initialize ASK Object
  project_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop()
{
  // Set buffer to size of expected message
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  if (project_driver.recv(buf, &buflen))
{ 

 // Message received with valid checksum
 str_out = string((char*)buf);
 
// Split string into two values
 for (int i = 0; i < str_out.length(); i++) {
        if (str_out.substring(i, i+1) == ",") {
          str_humid = str_out.substring(0, i);
          str_temp = str_out.substring(i+1);
          break;
 }
}
 // Print values
 
 display.setCursor(0,0);
 display.print("Temp: ");
 display.print(str_temp);
 display.print (" C");
 display.setCursor(0,1);
 display.print("Humid: ");
 display.print(str_humid);
 display.print (" %");
 
 }

}