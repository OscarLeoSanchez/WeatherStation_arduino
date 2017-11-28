#include <stdint.h>
#include "SparkFunBME280.h"
#include "Wire.h"
#include "SPI.h"


float var1=0;   // Velocidad viento  m/s
int var2=0;     // Temperatura  grados celsius
int var3=0;     // Humedad  %
int var4=0;     // Presion hPa
int var5=0;     // Radiacion W/m2
String var6="";  // Direccion 

//Variables encoder direccion
#define pinDirection A0

//Variables sensor radiacion
#define pinRadiation A1

//Variables encoder velocidad
int hits = 0;
float wheel_radius = 1;
volatile unsigned int current_time;
long time_interval = 1000;
 
//Variables sensor BME280

BME280 sensorPHT;



//Funciones encoder velocidad
float getSpeed(){
	float velocity = (hits*(wheel_radius*59)*0.01)/(time_interval); 
	hits = 0;
	current_time = millis();
	return velocity;
}

void count () {
	hits++;
}

//Funciones encoder direccion
String getDirection(){
        int reader = analogRead(pinDirection);
        if       (reader >=0 && reader < 32 )  return "N";
        else if (reader >=32 && reader < 96 ) return "NNE";
        else if (reader >=96 && reader < 160 ) return "NE";
        else if (reader >=160 && reader < 224 ) return "ENE";
        else if (reader >=224 && reader < 288 ) return "E";
        else if (reader >=288 && reader < 352 ) return "ESE";
        else if (reader >=352 && reader < 416 ) return "SE";
        else if (reader >=416 && reader < 480 ) return "SSE";
        else if (reader >=480 && reader < 544 ) return "S";
        else if (reader >=544 && reader < 607 ) return "SSO";
        else if (reader >=607 && reader < 671 ) return "SO";
        else if (reader >=671 && reader < 735 ) return "OSO";
        else if (reader >=735 && reader < 799 ) return "O";
        else if (reader >=799 && reader < 863 ) return "ONO";
        else if (reader >=863 && reader < 927 ) return "NO";
        else if (reader >=927 && reader < 991 ) return "NNO";
        return "N";        
}

//Funciones sensor radiacion

int getRadiation(){
  int rad = (analogRead(pinRadiation)*3*4.8)+30;
  return rad;
}

//Funciones programa


void setup () { 
	Serial.begin(9600);
	pinMode(pinDirection, INPUT); //
  pinMode(pinRadiation, INPUT);
	attachInterrupt(0, count, CHANGE);
	current_time = millis();
  sensorPHT.settings.commInterface = SPI_MODE;
  sensorPHT.settings.chipSelectPin = 53;
  sensorPHT.settings.runMode = 3; //  3, Normal mode
  sensorPHT.settings.tStandby = 0; //  0, 0.5ms
  sensorPHT.settings.filter = 0; //  0, filter off
  sensorPHT.settings.tempOverSample = 1;
  sensorPHT.settings.pressOverSample = 1;
  sensorPHT.settings.humidOverSample = 1;
  delay(10);
  sensorPHT.begin();
}

void loop (){	
  var2 = sensorPHT.readTempC();
  var3 = sensorPHT.readFloatHumidity();
  var4 = sensorPHT.readFloatPressure()/100;
  var5 = getRadiation();
  var6 = getDirection();
	if (millis() >= current_time + time_interval){
		var1=getSpeed();
	}
	
	delay(500);
}	








