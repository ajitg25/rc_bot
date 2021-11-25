#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define D1 5
#define D2 4
#define D3 0
#define D4 2 

const char *ssid = "Bot BMSCE";
const int port = 8080;

IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

ESP8266WebServer server(port);
int counter = 0;
String serVal = "S";
String preVal = "S";

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid);
  server.on("/move", HTTP_GET, handleMoveRequest);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Started Server");
  stops();
  delay(2000);

  pinMode(D1,OUTPUT);      //pins 1 and 2 are for L motor
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);      //pins 4 and 3 are for R other
  pinMode(D4,OUTPUT);
}
void forward()
{
  digitalWrite(D1,HIGH);
  digitalWrite(D2,LOW);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,LOW);
  
}
void left()
{
  digitalWrite(D1,LOW);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,LOW);

}
void right()
{
  digitalWrite(D1,HIGH);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,HIGH);
}
void backward()
{
  digitalWrite(D1,LOW);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,LOW);
  digitalWrite(D4,HIGH);
}
void stops()
{
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
}
void loop() 
{
 
  server.handleClient();
  if(!serVal.equals(preVal))
  {
    counter = 0;
  }
  if(serVal.equals("F"))
    forward();
  else if(serVal.equals("B"))
    backward();
  else if(serVal.equals("R"))
    right();
  else if(serVal.equals("L"))
    left();
  else if(serVal.equals("S"))
    stops();
  preVal = serVal;
    
}

void handleNotFound()
{
  server.send(404, "text / plain", "404: Not found");
}

void handleMoveRequest()
{
  if (!server.hasArg("dir"))
  {
    server.send(404, "text / plain", "Move: undefined");
    return;
  }
  String dir = server.arg("dir");
  Serial.println(dir);
  server.send(200, "text / plain", "Move: recieved");
  serVal = dir;
}
