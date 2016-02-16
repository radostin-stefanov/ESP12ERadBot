#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char *ssid = "Zumo Robot";
const char *password = "12345678";

ESP8266WebServer server(80);

//motor A connected between A01 and A02
//motor B connected between B01 and B02

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

int motor_speed;

void setup(){
  delay(1000);
  Serial.begin(115200);
    
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  WiFi.softAP(ssid, password);

  server.on("/", []() {
    
  String url = server.arg("pin");
  String state = url.substring(0,3);
  String value = url.substring(3);
  motor_speed = value.toInt();
 
  if (state == "ONA"){
  move(1, motor_speed, 1); //motor 1(A), full speed, left
  move(0, motor_speed, 1); //motor 2(B), full speed, left
  delay(250); //hold for 250ms until move again
  }
  else if (url == "OFFA"){

  }
  else if (state == "ONB"){

  }
  else if (url == "OFFB"){

  }
  else if (state == "ONC"){

  }
  else if (url == "OFFC"){

  }
  else if (state == "OND"){

  }
  else if (url == "OFFD"){

  }
});
 
  server.begin();
}


void loop(){
    server.handleClient();
//  move(1, 10, 1); //motor 1(A), full speed, left
//  move(0, 10, 1); //motor 2(B), full speed, left
//  delay(250); //hold for 250ms until move again
}


void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}
