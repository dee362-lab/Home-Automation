#include <ESP32Servo.h>
#include <Arduino.h>
#include <WiFi.h>
#include<WiFiClient.h>
#include <NTPClient.h>
#include<WiFiUdp.h>
#include <DHT.h>
#include <HTTPClient.h>
#include "esp_task_wdt.h"





//difine pins and for actuator and sensors
#define servoPin 15
# define LED 16
# define fan 17
#define PIR 18

//variables for the NTP
const long offset=19800;
const char* server="asia.pool.ntp.org";
const long interval=6000;

//creat the objects
WiFiUDP ntpudp;
NTPClient timeclient(ntpudp,server,offset,interval);
DHT dht(4, DHT22);
Servo door;
HTTPClient http;

//define the id and password for wifi

const char *name="Wokwi-GUEST";
const char *password="";
const char *serverURL="http://192.168.56.1:5000/data";

//for locking the door
int currentTime;
int preTime=0;
int thesh=10;
int motion;
bool doorlock=false;
 
void autolock(void* pvParameter){
  (void)pvParameter;
  while(1){
    currentTime=timeclient.getMinutes();
    motion =digitalRead(PIR);
    if(motion){
      preTime=currentTime;
    }
    if(!doorlock && currentTime-preTime>=interval){
      lockDoor();
      preTime=currentTime;
      doorlock=true;
      Serial.println("door locked");
    }
    esp_task_wdt_reset(); 
     vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


void lockDoor(){
  door.write(0);
  doorlock=true;
  Serial.println("door lock");
    
}  
void unlockDoor(){
  door.write(90);
  doorlock=false;
  Serial.println("door unlock");
  
}

void SendData(void* pvParameter){
  //send the sensor data
    float temperature;
    float humidity;
    
  (void)pvParameter;
  
  while(1){
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    if(WiFi.status()==WL_CONNECTED){

      http.begin(serverURL);
      http.addHeader("Content-Type", "application/json");
      String postData = "{\"temperature\":" + String(temperature) +
      ", \"humidity\":" + String(humidity) + "}";

      Serial.println("Sending Data...");

      int httpResponseCode = http.POST(postData);
        
      Serial.println("Data Sent: " + postData);
      Serial.println("Server Response: " + String(httpResponseCode));

      http.end();
      Serial.println("send the data");
    } else {
        Serial.println("Wi-Fi not connected!");
    }
    esp_task_wdt_reset(); 
    vTaskDelay(1000 / portTICK_PERIOD_MS);

  }
  
}

//void recData(void* pvParameter){}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(PIR, INPUT);
 esp_task_wdt_deinit(); 


   WiFi.begin(name,password);
 while(WiFi.status()!=WL_CONNECTED){
  delay(1000);
  Serial.println("connectig....");
 }
 Serial.println("connected");
  door.attach(servoPin);
  door.write(0);
  dht.begin();
  timeclient.begin();
  timeclient.update();
  Serial.println();



 //initilise the wifi 


 //door.attach(servoPin);
 xTaskCreate(autolock,"autolock",8192,NULL,1,NULL);
 xTaskCreate(SendData,"sending data to the server",8192,NULL,1,NULL);
  Serial.println("Task WDT Debug: Checking active tasks...");
 vTaskStartScheduler();
 
}

String voice;

void loop() {



    }
