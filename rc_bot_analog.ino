#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  D3         // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2  D4          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  D5           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  D6           // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h>  
Servo servo;

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "bot2";
ESP8266WebServer server(80);

void setup() {
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
 servo.attach(D8);
 servo.write(180);
  delay(100);
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ analogWrite(D3, 100);
          analogWrite(D6, 100);
          analogWrite(D4, 0);
          analogWrite(D5, 0);
      delay(100);  
      analogWrite(D3, 0);
      analogWrite(D4, 0);
      analogWrite(D5, 0);
      analogWrite(D6, 0);
      Serial.println("f");
}

void goBack(){analogWrite(D3, 0);
          analogWrite(D4, 100);
          analogWrite(D5, 100);
          analogWrite(D6, 0);
      delay(100);
      analogWrite(D3, 0);
      analogWrite(D4, 0);
      analogWrite(D5, 0);
      analogWrite(D6, 0);
      Serial.println("b");
  }

void goRight(){ analogWrite(D3, 0);
          analogWrite(D4, 100);
          analogWrite(D5, 0);
          analogWrite(D6, 100);
          delay(40);
          analogWrite(D3, 0);
          analogWrite(D4, 0);
          analogWrite(D5, 0);
          analogWrite(D6, 0);
          Serial.println("r");
}

void goLeft(){
      analogWrite(D3, 100);
          analogWrite(D4, 0);
          analogWrite(D5, 100);
          analogWrite(D6, 0);
          delay(40);
          analogWrite(D3, 0);
          analogWrite(D4, 0);
          analogWrite(D5, 0);
          analogWrite(D6, 0);
          Serial.println("l");
        
  }

void goAheadRight(){analogWrite(D3, 0);
          analogWrite(D4, 0);
          analogWrite(D5, 0);
          analogWrite(D6, 0);
          servo.write(70);
         // delay(500);
          //servo.write(180);
      
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  
    analogWrite(D3, 0);
          analogWrite(D4, 0);
          analogWrite(D5, 0);
          analogWrite(D6, 0);
          
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
