#include <ESP8266WiFi.h>
#define D1 5
#define D2 4
#define D3 0
#define D4 2 

WiFiClient client;                     //hosting a web server
WiFiServer server(80);

const char* ssid = "robo";            //userid and password of the respective network your nodemcu is connecting to
const char* password = "ajit123#";

String  data =""; 

void setup() 
{
  Serial.begin(115200);
  connect_wifi();
  server.begin();

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
 
  client = server.available();
  if (!client) return; 
  data = getclientdata ();

  if (data == "F")                      //use the forward and back buttons on the app to turn the onboard LED ON/OFF
    { 
      forward();
         //ACTIVE LOW OPERATION
    }
  if (data == "B") 
    {
      backward();
      
    }
  if (data == "L") 
    {
      left();
      
    }
  if (data == "R") 
    {
      right();
      
    }
    
}

void connect_wifi()
{
  //WiFi.mode(WIFI_STA);`
  WiFi.begin(ssid,password);
  
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  
  Serial.println("\n\n");
  Serial.println("WiFi connected");
  Serial.print("NodeMCU Local IP: ");         //dynamically assigned IP over which your server is hosted
  Serial.println((WiFi.localIP()));
}

String getclientdata (void)
{
  while(!client.available())                  //wait till client is avaliable
  {
    delay(1); 
  }

                                                  //read the data from client
  String data = client.readStringUntil('\r');

  Serial.println("");
  Serial.print("INCOMING DATA: ");                //recognising the structure of incoming data
  Serial.println(data);
  Serial.print("length: ");
  Serial.println(data.length());
  Serial.println("END OF DATA");

  data.remove(0,12);                              //parse the input data to obtain only the required attributes
  data.remove(1,9);

  Serial.print("Parsed data:");
  Serial.println(data);
  
  Serial.print("parsed data length: ");
  Serial.println(data.length());
  
  return data;
}
