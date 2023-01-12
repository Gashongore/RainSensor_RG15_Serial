#include "Particle.h"
#include <stdlib.h>
#include<string.h>

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


float acc_f=0, eventAcc_f=0, totalAcc_f=0, rInt_f=0;



void setup()
{
Serial1.begin(9600,SERIAL_8N1);
  
Serial1.write('c');
Serial1.write('\n');

}


void loop() {
 

String response = Serial1.readStringUntil('\n');

if (response.startsWith("Acc")) {
    char acc[7], eventAcc[7], totalAcc[7], rInt[7], unit[4];
    sscanf(response.c_str(),"%*s %s %[^,] , %*s %s %*s %*s %s %*s %*s %s", acc, unit, eventAcc, totalAcc, rInt);


acc_f=atof(acc);
eventAcc_f=atof(eventAcc);
totalAcc_f=atof(totalAcc);
rInt_f=atof(rInt);


Particle.publish("Accumulated Rain",acc);
Particle.publish("Amount of rain for this event",eventAcc);
Particle.publish("Total amount of rain",totalAcc);
Particle.publish("Current rain intensity",rInt);

}

  delay(3000);
}


