//Linked library for DHT11 located in platform.ini file --> lib_deps = https://github.com/dhrubasaha08/DHT11 @ ^2.1.0 
#include <Arduino.h>
#include <DHT11.h>
const int temp_sensor_pin = 2;

DHT11 temp_sensor(temp_sensor_pin); //declares a new object called temp_sensor from the DHT11 class. The var name in ( ) is called a constructors. They give the object needed default values.

//Function Prototypes. Needed in C++, the compiler needs to know about these functions first before using.
void read_humidity();
void read_temp();
float c_to_f(float temp_in_c);

void setup() {
  
  Serial.begin(9600);
  temp_sensor.setDelay(2000); //Prob set to every 30 minutes for plant care.
}

void loop() {
  read_humidity();
  read_temp();
}

void read_humidity(){
  float humidity = temp_sensor.readHumidity();
  if(humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT ){    //This checks for a checksum error (error during transmission from sensor to arduino) and a timeout error (hardware defect). If these are not present it reads temp, if the are it will give an error string.
    Serial.println("Humidity Reading: " + String(humidity) + "%");
  } else{
    Serial.println(DHT11::getErrorString(humidity));
  }
}

void read_temp(){
  float temp = temp_sensor.readTemperature();
  if(temp != DHT11::ERROR_CHECKSUM && temp != DHT11::ERROR_TIMEOUT){
    float converted_temp = c_to_f(temp);
    Serial.println("Temperature Reading: " + String(converted_temp) + " degrees.");
  } else{
    Serial.println(DHT11::getErrorString(temp));
  }
}

float c_to_f(float temp_in_c){
  return (temp_in_c) * (9./5.) + 32;  //REMEMBER TO PUT A DECIMAL POINT SO THAT THE INTS BECOME FLOATS SO THE MATH CHECKS OUT
}
