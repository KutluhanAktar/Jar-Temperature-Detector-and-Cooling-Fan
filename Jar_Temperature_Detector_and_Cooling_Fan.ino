         /////////////////////////////////////////////  
        //  Jar Temperature Detector and Cooling   //
       //                  Fan                    //
      //    -----------------------------        //
     //             Arduino Nano                //           
    //           by Kutluhan Aktar             // 
   //                                         //
  /////////////////////////////////////////////

// While measuring temperature on a project, you may need to act instantly to make connected parts cooler to protect the components as a fan works in a computer.
// Basically, this project is about to detecting temperature in Celsius above 25 degree to run the fan to descend it under the threshold, of course you can change it.
// Also, you will be able to monitor the temperature in Celsius and Fahrenheit along with the piezo disk sensor on the serial monitor by taking following steps down below.
//
// Connections
// Arduino Nano :           
//                                 Piezo Disk Sensor
// 5V  --------------------------- 5V
// GND --------------------------- GND
//                                 DS18B20 Temperature Sensor
// 5V  --------------------------- 5V
// D2  --------------------------- OUT
// GND --------------------------- GND
//                                 L9110 Fan Motor
// 5V  --------------------------- 5V
// GND --------------------------- GND
// D3  --------------------------- INA
// D4  --------------------------- INB


// Libraries for DS18B20 Temperature Sensor
#include <OneWire.h>
#include <DallasTemperature.h>

// Attach the bus pin to the temperature sensor.
#define ONE_WIRE_BUS 2

// Initial OneWire and DallasTemperature Libraries.
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

// Define the piezoelectric disk pin to read.
#define piezoDisk A0

// Define INA and INB pins to change fan directions.
#define INA 3
#define INB 4

// Define variables to save values.
float Celsius, Fahrenheit;
int piezo;

// This boolean runs the fan if the temperature is above 25 Celsius.
boolean HighTemperature;

void setup() {
Serial.begin(9600);

pinMode(INA, OUTPUT);
pinMode(INB, OUTPUT);

// Activate the DS18B20.
DS18B20.begin();

}

void loop() {
get_Variables_From_Sensors();

digitalWrite(INA, LOW);
digitalWrite(INB, LOW);
// Depending on the state of the piezo disk, either end task or continue.
if(Celsius > 25 && piezo < 100){
   HighTemperature = true;
    while(HighTemperature == true){
      get_Variables_From_Sensors();
      digitalWrite(INA, HIGH);
      digitalWrite(INB, LOW);
        if(Celsius > 80){
            // At this temperature, change the fan direction opposite as an indicator.
            digitalWrite(INA, LOW);
            digitalWrite(INB, HIGH);
          }else if(Celsius < 25 || piezo > 100){
            // If temperature is below 25 Celsius, halt the task.
            HighTemperature = false;
          }
    }
}


}

void get_Variables_From_Sensors(){
  // Get data from the piezo disk.
  piezo = analogRead(piezoDisk);
  // Get temperature in Celsius and Fahrenheit from the DS18B20.
  DS18B20.requestTemperatures(); 
  Celsius = DS18B20.getTempCByIndex(0);
  Fahrenheit = DS18B20.toFahrenheit(Celsius);

  // Debug variables.
  Serial.print("Celsius: ");
  Serial.print(Celsius);
  Serial.print("\t\t");
  Serial.print("Fahrenheit: ");
  Serial.print(Fahrenheit);
  Serial.print("\t\t");
  Serial.print("PiezoDisk: ");
  Serial.print(piezo);
  Serial.print("\n");
  

}
