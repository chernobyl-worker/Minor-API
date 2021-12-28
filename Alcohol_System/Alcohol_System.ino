#include <WiFi.h>
#include <HTTPClient.h>

#define Buzzer 32
#define MQ3pin 34
#define relayPin 14
#define redPin 26
#define greenPin 27
#define bluePin 25

bool MQ3val = 0;

const char* ssid = "b46";
const char* password = "fluffybolt123";

const char* serverName = "http://192.168.106:5000/";
bool sent = false;
bool flag = false;

void RGB_SET(int red = 256, int green = 256, int blue = 256) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  Serial.begin(115200);
  pinMode(MQ3pin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  digitalWrite(relayPin, LOW);
//
//  digitalWrite(ledPin, HIGH);
//  delay(500);
//  digitalWrite(ledPin, LOW);
//  
  // WIFI setup
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    RGB_SET(256,256,0);
    delay(250);
    RGB_SET();
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Buzzer Setup 
  ledcSetup(0, 400, 8);
  ledcAttachPin(Buzzer, 0);
  
  // MQ3 Wait
  Serial.println("MQ3 warming up!");
  int wait = 0;
  while(wait < 20000) {
    RGB_SET(256-(wait/100),256,256);
    delay(900);
    RGB_SET();
    delay(100);
    wait += 1000;
  }
//  delay(20000); // allow the MQ3 to warm up
  RGB_SET(256,0,256);
  delay(100);
}

void loop() {
  MQ3val = !digitalRead(MQ3pin);
  Serial.print("MQ3 value: ");
  Serial.println(MQ3val);
  if(MQ3val && !flag) {
    RGB_SET(128, 128, 128);
    ledcWrite(0, 256);
    ledcWriteTone(0, 400);
    delay(1000);
    ledcWrite(0,0);
    delay(14000);
    MQ3val = !digitalRead(MQ3pin);
    Serial.print("MQ3 value after delay: ");
    Serial.println(MQ3val);
    if(MQ3val) {
      RGB_SET(0, 256, 256);
      for(int i=0; i<3; i++) {
        ledcWrite(0,255);
        ledcWriteTone(0,500);
        delay(500);
        ledcWrite(0,0);
        delay(500);
      }
      flag = true;
    } else {
      RGB_SET(256, 0, 256);
    }
  }
  
  if(!sent && flag) {
    digitalWrite(relayPin, HIGH);
    if(WiFi.status()== WL_CONNECTED){
      sent = true;
      
      WiFiClient client;
      HTTPClient http;
      
      http.begin(client, serverName);
      
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"id\":123,\"email\":\"tushargupta1999@gmail.com\",\"chatid\": 1108168221}");
//      int httpResponseCode = http.POST("{\"id\":123,\"email\":\"mashirdav123@gmail.com\"}");

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
  delay(2000);
}
