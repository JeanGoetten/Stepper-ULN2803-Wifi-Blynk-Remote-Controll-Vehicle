#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Stepper.h>

#define BLYNK_PRINT Serial


char auth[] = "XvBFoiS0bmFclTcmOx7aK_VCIyzd07py";
char ssid[] = "StarTec_Jean Carlos";
char pass[] = "jean12345";

int pinValue_speed;

Stepper motorRight(pinValue_speed, D2, D3, D4, D5);
Stepper motorLeft(pinValue_speed, D5, D6, D7, D8);

bool left_motor_check, right_motor_check;  

void setup() {
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);

}

BLYNK_WRITE(V0){
  
  pinValue_speed = param.asInt(); 
  
  
 }
BLYNK_WRITE(V1){
  
  int pinValue_left = param.asInt(); 
  
  if(pinValue_left == 1){
    left_motor_check = true;
    }
  else{
    left_motor_check = false; 
    }
  
 }
BLYNK_WRITE(V2){
  
  int pinValue_right = param.asInt(); 
  
  if(pinValue_right == 1){
    right_motor_check = true; 
    }
   else{
    right_motor_check = false; 
    }
  
 }

void loop() {
  Blynk.run();

  if(left_motor_check){
    motorLeft.step(pinValue_speed); 
    Serial.print("Motor Left Speed Moment: "); 
    Serial.print(pinValue_speed); 
    Serial.print("\n"); 
    delay(1);
  }
  if(right_motor_check){
    motorRight.step(pinValue_speed); 
    Serial.print("Motor Right Speed Moment: "); 
    Serial.print(pinValue_speed); 
    Serial.print("\n"); 
    delay(1);
  }
  delay(10); 
}
