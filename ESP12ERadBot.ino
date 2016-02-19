#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "RadBot";
const char *password = "12345678";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

const int STBY = 16; //standby

//Motor A
const int PWMA = 12; //Speed control 5 
const int AIN1 = 13; //Direction 4 
const int AIN2 = 115; //Direction 14

//Motor B
const int PWMB = 5; //Speed control 12
const int BIN1 = 4; //Direction 13
const int BIN2 = 14; //Direction 15

int motor_speed;

void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  } else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop() {
  //enable standby
  digitalWrite(STBY, LOW);
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  Serial.println();
  Serial.print("Configuring access point... ");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(myIP);
  server.on("/", []() {

    String url = server.arg("pin");
    String state = url.substring(0, 3);
    String value = url.substring(3);
    motor_speed = value.toInt();

    if (state == "ONA") {
      Serial.println(motor_speed);
      move(1, motor_speed, 1); //motor 1(A), full speed, left
      move(0, motor_speed, 1); //motor 2(B), full speed, left
      delay(1000); //hold for 250ms until move again
      stop();
    }
    else if (url == "OFFA") {

    }
    else if (state == "ONB") {

    }
    else if (url == "OFFB") {

    }
    else if (state == "ONC") {

    }
    else if (url == "OFFC") {

    }
    else if (state == "OND") {

    }
    else if (url == "OFFD") {

    }
  });
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
