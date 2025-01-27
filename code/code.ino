
#include <Servo.h>
#include <Arduino_FreeRTOS.h>

#define servoPin 10

const TaskHandle_t BluetoothOp=NULL;
const TaskHandle_t Autolock=NULL;
bool doorlock= true;
Servo door;
//Pin declration
const int trig=3,echo=2;
const int led=11;
const int fan=13;

//important variables
int duration;
int distance;
unsigned long previousMillis= 0;   // stores the last time an object was detected
const long interval = 20000;         // interval to wait for (20 seconds)

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
  
void autolock(void* pvParameter){
  (void)pvParameter;
  while(1){
    if(!doorlock && millis()-previousMillis>=interval){
      door.write(0);
      previousMillis=millis();
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
  previousMillis=millis();
}



void setup() {
 pinMode(fan,OUTPUT);
 pinMode(led,OUTPUT);
 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);
 Serial.begin(9600);
 door.attach(servoPin);
 xTaskCreate(autolock,"autolock",128,NULL,1,&Autolock);
 xTaskCreate(BluetoothTask,"bluetoothOperation",128,NULL,1,&BluetoothOp);
 
}

String voice;

void loop() {

}
