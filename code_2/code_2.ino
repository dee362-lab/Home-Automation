#include <Servo.h>
#include <Arduino.h>
#include <WiFi.h>
#include<WiFiClient.h>
#include <NTPClient.h>
#include<WiFiUdp.h>
#include <DHT.h>
#include <HTTPClient>



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
WiFiUdp ntpudp;
NTPClient timeclient(ntpudp,server,offset,intervel);
DHT dht(4, DHT22);
Servo door;
HTTPClient http;

//define the id and password for wifi

const char *name="Wokwi-GUEST";
const char *password="";
const char *serverURL="http://127.0.0.1:5000/data";

//for locking the door
int currentTime;
int preTime=0;
int thesh=10;
int motion;


 
/*
//creat task for the bluetooth functin 
void BluetoothTask(void* pvParameter){
  (void)pvParameter;

  while(1){
   if( Serial.available()){
    String command=Serial.readStringUntil('\n');
    command.trim();
    Serial.println("command: "+command);
  if(command.equalsIgnoreCase("Turn on light")){
    digitalWrite( led, HIGH);}
  if(command.equalsIgnoreCase("Turn off light")){
    digitalWrite( led, LOW);}
  if(command.equalsIgnoreCase("Turn on fan")){
    digitalWrite( fan, HIGH);}
  if(command.equalsIgnoreCase("Turn off fan")){
    digitalWrite( fan, LOW);}
  if(command.equalsIgnoreCase("opoen the door")){
    lockDoor();}
  if(command.equalsIgnoreCase("close the door")){
    unlockDoor();
  
   }
  }
  vTaskDelay(pdMS_TO_TICKS(100));
  }
}


*/  
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
    }
    vTaskDelay(pdMS_TO_TICKS(500));
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

      int httpResponseCode = http.POST(postData);
        
      Serial.println("Data Sent: " + postData);
      Serial.println("Server Response: " + String(httpResponseCode));

      http.end();
    } else {
        Serial.println("Wi-Fi not connected!");
    }

  }
  
}

void recData(void* pvParameter){

}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(PIR, INPUT);
  door.attach(servoPin);
  door.write(0);
  dht.begin();
  timeclient.begin();
  timeclient.update();
  Serial.println();



 //initilise the wifi 
 WiFi.begin(name,password);
 while(WiFi.status()!=WL_CONNECTED){
  delay(1000);
  Serial.println("connectig....");
 }
 Serial.println("connected");

 //door.attach(servoPin);
 //xTaskCreate(autolock,"autolock",128,NULL,1,NULL);
 //xTaskCreate(BluetoothTask,"bluetoothOperation",128,NULL,1,NULL);
 
}

String voice;

void loop() {

    Serial.println(temperature);
    Serial.println(humidity);

    }
