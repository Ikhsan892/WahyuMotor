// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

void setup()
{  
  Serial.begin(9600);
  
  emon1.current(39, 1.65);             // Current: input pin, calibration.
}

void loop()
{
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  
//  Serial.print(Irms*220.0);	       // Apparent power
//  Serial.print(" ");
  if(Irms < 0.1){
    Irms = 0;
  }
  Serial.print(Irms);		       // Irms
  Serial.println(" A");           // Irms

  
  delay(1000);
}
