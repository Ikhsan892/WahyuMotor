#include <Filters.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6jpcaK3_T"
#define BLYNK_TEMPLATE_NAME "Project Monitoring RPM Motor 1 Phase"
#define BLYNK_AUTH_TOKEN "SRWz4zwecMCT7gBsdbRcS33sGiVOf6G0"
#define BLYNK_PRINT Serial

#define PIN_VOLTAGE 34

float testFrequency = 50;                     // signal frequency (Hz)
float windowLength = 40.0/testFrequency;     // how long to average the signal, for statistist

int Sensor = 0;    

float intercept = -0.04;  // adjust untuk kalibrasi -0.04
float slope = 0.0086;   // adjust untuk kalibrasi awal 0.964
float current_Volts;      

unsigned long printPeriod = 1000;     //Refresh rate
unsigned long previousMillis = 0;

char ssid[] = "Elektronika BKM 2";
char pass[] = "roboticbkm2";

BlynkTimer timer;

void testSendDataToGauge()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, 100);
}

void sendVoltage(){ 
  Serial.print( "Voltage Blynk: " );
  Serial.println( current_Volts );
  Blynk.virtualWrite(V0, current_Volts);   
}

BLYNK_CONNECTED() {
  Serial.println("Connected to Blynk Server");
}

void setup() {
  Serial.begin(115200);
  Serial.println("AC Voltmeter");


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendVoltage); 
}

void loop() {      
  RunningStatistics inputStats;               
  inputStats.setWindowSecs( windowLength );
  while( true ) {   
    Sensor = analogRead(PIN_VOLTAGE);                // read the analog in value:
    inputStats.input(Sensor);                   // log to Stats function
        
    if((unsigned long)(millis() - previousMillis) >= printPeriod) {
      previousMillis = millis();                // update time every second
      
      current_Volts = intercept + slope * inputStats.sigma(); //Calibartions for offset and amplitude
      current_Volts= current_Volts*(49.3231);                //Further calibrations for the amplitude     
      
      if (current_Volts < 30){
        current_Volts = 0;
      }
      
      Serial.print( "Voltage: " );
      Serial.println( current_Volts );
      
    }
    Blynk.run(); 
    timer.run(); 
  }
}
