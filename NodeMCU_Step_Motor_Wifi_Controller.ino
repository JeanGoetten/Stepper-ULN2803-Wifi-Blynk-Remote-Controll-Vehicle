#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Stepper.h>

#define BLYNK_PRINT Serial


char auth[] = "XvBFoiS0bmFclTcmOx7aK_VCIyzd07py";
char ssid[] = "StarTec_Jean Carlos";
char pass[] = "jean12345";

int steppes_per_revolution = 200;
int steppes_live = 1; 
int pinValue_speed;

Stepper motorRight(steppes_per_revolution, D1, D2, D3, D4);
Stepper motorLeft(steppes_per_revolution, D5, D6, D7, D8);

bool left_motor_check, right_motor_check;  

void setup() {
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);

}

BLYNK_WRITE(V0){
  
  pinValue_speed = param.asInt(); 

  if(pinValue_speed < 1){
    pinValue_speed = 1; 
  }

  motorLeft.setSpeed(pinValue_speed); 
  motorRight.setSpeed(pinValue_speed);
  
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
 BLYNK_WRITE(V3){
  
  int pinValue_backward = param.asInt(); 

  if(pinValue_backward){
    steppes_live = -1; 
  }else{
    steppes_live = 1; 
  }
  
 }

void loop() {
  Blynk.run();

  if(left_motor_check){
    motorLeft.step(steppes_live); 
    Serial.print("Motor Left Speed Moment: "); 
    Serial.print(pinValue_speed); 
    Serial.print("\n"); 
    delay(1);
  }
  if(right_motor_check){
    motorRight.step(steppes_live); 
    Serial.print("Motor Right Speed Moment: "); 
    Serial.print(pinValue_speed); 
    Serial.print("\n"); 
    delay(1);
  }else{
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
    Serial.print("Motor released"); 
    Serial.print("\n"); 
    delay(1);
  }
  delay(1); 
}
