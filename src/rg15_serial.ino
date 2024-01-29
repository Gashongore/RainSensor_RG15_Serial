#include "Particle.h"
#include <stdlib.h>
#include <string.h>

// Prototypes and System Mode calls
SYSTEM_MODE(SEMI_AUTOMATIC);                                                                     // This will enable user code to start executing automatically.
SYSTEM_THREAD(ENABLED);                                                                     // Means my code will not be held up by Particle processes.
STARTUP(System.enableFeature(FEATURE_RESET_INFO));

/*
1. acc : Amount of rain since last message (see update_interval), in mm. Only on RG-15.
2. event_acc : Amount of rain for this event (i.e. since it last stopped raining), in mm. Only on RG-15.
3. total_acc : Total amount of rain this sensor has ever measured, in mm. Only on RG-15.
4. r_int : Current rain intensity in mm/h. Only on RG-15.
5. update_interval : The interval to check the sensor. 
*/


double acc_f=0;
double eventAcc_f=0;
double totalAcc_f=0;
double rInt_f=0;

SerialLogHandler logHandler;

void setup()
{
Serial1.begin(9600,SERIAL_8N1);
  
Serial1.write('c');
Serial1.write('\n');

Serial.begin(9600);

}

void loop(){
     readRainSensor();

     delay(3000);
  
}
void readRainSensor(){
  String response;
  while (response.length() == 0) {
    response = Serial1.readStringUntil('\n');
    // Optionally, add a small delay here to avoid continuous reading
    delay(100);
  }
  if(response.startsWith("Acc")) {
    char acc[7], eventAcc[7], totalAcc[7], rInt[7], unit[4];
    sscanf(response.c_str(), "%*s %6s %[^,] , %*s %6s %*s %*s %6s %*s %*s %6s", acc, unit, eventAcc, totalAcc, rInt);
    
    Serial.print("Accumulation: ");
    Serial.print(atof (acc),3);  
    Serial.println(unit);
    Serial.print("Event Accumulation: ");
    Serial.print(atof (eventAcc),3);  
    Serial.println(unit);
    Serial.print("Total Accumulation: ");
    Serial.print(atof (totalAcc),3);  
    Serial.println(unit);
    Serial.print("IPH: ");
    Serial.print(atof (rInt), 3);
    Serial.println(" IPH\n");

    // do we need to flash the serial??


    
     // Publish the values as events
    // sensorData.totalAcc = atof(totalAcc);
    // sensorData.event_Accumulation = atof(eventAcc);
    // // sensorData.totalAcc = atof(totalAcc);
    // Particle.publish("Accumulation", String(atof(acc), 3), PRIVATE);
    // Particle.publish("Event Accumulation", String(atof(eventAcc), 3), PRIVATE);
    // Particle.publish("Total Accumulation", String(atof(totalAcc), 3), PRIVATE);
    // Particle.publish("IPH", String(atof(rInt), 3), PRIVATE);
    // Particle.publish("IPH",String(atof (rInt), 3),PRIVATE);
  }
}

/*
void loop() {
 

String response = Serial1.readStringUntil('\n');

if (response.startsWith("Acc")) {
    char acc[7], eventAcc[7], totalAcc[7], rInt[7], unit[4];
    sscanf(response.c_str(),"%*s %s %[^,] , %*s %s %*s %*s %s %*s %*s %s", acc, unit, eventAcc, totalAcc, rInt);


acc_f=atof(acc);
eventAcc_f=atof(eventAcc);
totalAcc_f=atof(totalAcc);
rInt_f=atof(rInt);



//Particle.publish("Accumulated Rain",acc);
//Particle.publish("Amount of rain for this event",eventAcc);
//Particle.publish("Total amount of rain",totalAcc);
//Particle.publish("Current rain intensity",rInt);


Serial.print("Accumulated Rain");
Serial.println(acc_f);

Serial.print("Amount of rain for this event");
Serial.println(eventAcc_f);

Serial.print("Total amount of rain");
Serial.println(totalAcc_f);

Serial.print("Current rain intensity");
Serial.println(rInt_f);

}

  delay(3000);
}

*/
