#include <WiFi.h>
#include <ESP32Servo.h>

Servo servoA;
Servo servoB;
Servo servoC;
Servo servoD;


//const char* ssid = "capstone-wifi";
//const char* password = "password";

const char* ssid = "Barronsrevenge";
const char* password = "98765432";

// const int LEDpin = 27;

float deg = 0;          // variable to store the servo position
int servoPin = 27; 
int servoPinB = 25;
int servoPinC = 2;
int servoPinD = 17;

WiFiServer server(80);

void setup() {

  Serial.begin(9600);
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servoA.setPeriodHertz(50);    // standard 50 hz servo
	servoA.attach(servoPin, 500, 2500);
  servoA.write(degreeToPos(50)); //22 = closed
  delay(10000);
  servoA.write(degreeToPos(22));


	servoB.setPeriodHertz(50);    // standard 50 hz servo
	servoB.attach(servoPinB, 500, 2500);
  servoB.write(degreeToPos(50)); //22 = closed
  delay(10000);
  servoB.write(degreeToPos(22));

  servoC.setPeriodHertz(50);    // standard 50 hz servo
	servoC.attach(servoPinC, 500, 2500);
  servoC.write(degreeToPos(50)); //22 = closed
  delay(10000);
  servoC.write(degreeToPos(22));

  servoD.setPeriodHertz(50);    // standard 50 hz servo
	servoD.attach(servoPinD, 500, 2500);
  servoD.write(degreeToPos(50)); //22 = closed
  delay(10000);
  servoD.write(degreeToPos(22));

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.println("Connected to the WiFi network");
  server.begin();

}

void loop() {


  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // For debugging

        currentLine += c;
        

        // Check for end of line
        if (c == '\n' || c == '\r') {
          Serial.println("Received command: " + currentLine);
          
          // Respond to the client
          if (currentLine.startsWith("Aten")) {
            delay(2000);
            Serial.println("ten");
            servoA.write(degreeToPos(60));
            delay(2000);
          } else if (currentLine.startsWith("Anine")) {
            delay(2000);
            servoA.write(degreeToPos(31));
            Serial.println("nine");
            delay(2000);
          } else if (currentLine.startsWith("Aeight")) {
            delay(2000);
            servoA.write(degreeToPos(30));
            Serial.println("eight");
            delay(2000);
          } else if (currentLine.startsWith("Aseven")) {
            delay(2000);
            servoA.write(degreeToPos(29));
            delay(2000);
          } else if (currentLine.startsWith("Asix")) {
            delay(2000);
            servoA.write(degreeToPos(28));
            delay(2000);
          } else if (currentLine.startsWith("Afive")) {
            delay(2000);
            servoA.write(degreeToPos(27));
            delay(2000);
          } else if (currentLine.startsWith("Afour")) {
            delay(2000);
            servoA.write(degreeToPos(26));
            delay(2000);
          } else if (currentLine.startsWith("Athree")) {
            delay(2000);
            servoA.write(degreeToPos(25));
            delay(2000);  
          } else if (currentLine.startsWith("Atwo")) {
            delay(2000);
            servoA.write(degreeToPos(24));
            delay(2000);
          } else if (currentLine.startsWith("Aone")) {
            delay(2000);
            servoA.write(degreeToPos(23));
            delay(2000);
          } else if (currentLine.startsWith("Azero")) {
            delay(2000);
            servoA.write(degreeToPos(22));
            delay(2000);
          }

          else if (currentLine.startsWith("Bten")) {
            delay(2000);
            Serial.println("ten");
            servoB.write(degreeToPos(60));
            delay(2000);
          } else if (currentLine.startsWith("Bnine")) {
            delay(2000);
            servoB.write(degreeToPos(31));
            Serial.println("nine");
            delay(2000);
          } else if (currentLine.startsWith("Beight")) {
            delay(2000);
            servoB.write(degreeToPos(30));
            Serial.println("eight");
            delay(2000);
          } else if (currentLine.startsWith("Bseven")) {
            delay(2000);
            servoB.write(degreeToPos(29));
            delay(2000);
          } else if (currentLine.startsWith("Bsix")) {
            delay(2000);
            servoB.write(degreeToPos(28));
            delay(2000);
          } else if (currentLine.startsWith("Bfive")) {
            delay(2000);
            servoB.write(degreeToPos(27));
            delay(2000);
          } else if (currentLine.startsWith("Bfour")) {
            delay(2000);
            servoB.write(degreeToPos(26));
            delay(2000);
          } else if (currentLine.startsWith("Bthree")) {
            delay(2000);
            servoB.write(degreeToPos(25));
            delay(2000);  
          } else if (currentLine.startsWith("Btwo")) {
            delay(2000);
            servoB.write(degreeToPos(24));
            delay(2000);
          } else if (currentLine.startsWith("Bone")) {
            delay(2000);
            servoB.write(degreeToPos(23));
            delay(2000);
          } else if (currentLine.startsWith("Bzero")) {
            delay(2000);
            servoB.write(degreeToPos(22));
            delay(2000);
          }
          else if (currentLine.startsWith("Cten")) {
            delay(2000);
            Serial.println("ten");
            servoC.write(degreeToPos(60));
            delay(2000);
          } else if (currentLine.startsWith("Cnine")) {
            delay(2000);
            servoC.write(degreeToPos(31));
            Serial.println("nine");
            delay(2000);
          } else if (currentLine.startsWith("Ceight")) {
            delay(2000);
            servoC.write(degreeToPos(30));
            Serial.println("eight");
            delay(2000);
          } else if (currentLine.startsWith("Cseven")) {
            delay(2000);
            servoC.write(degreeToPos(29));
            delay(2000);
          } else if (currentLine.startsWith("Csix")) {
            delay(2000);
            servoC.write(degreeToPos(28));
            delay(2000);
          } else if (currentLine.startsWith("Cfive")) {
            delay(2000);
            servoC.write(degreeToPos(27));
            delay(2000);
          } else if (currentLine.startsWith("Cfour")) {
            delay(2000);
            servoC.write(degreeToPos(26));
            delay(2000);
          } else if (currentLine.startsWith("Cthree")) {
            delay(2000);
            servoC.write(degreeToPos(25));
            delay(2000);  
          } else if (currentLine.startsWith("Ctwo")) {
            delay(2000);
            servoC.write(degreeToPos(24));
            delay(2000);
          } else if (currentLine.startsWith("Cone")) {
            delay(2000);
            servoC.write(degreeToPos(23));
            delay(2000);
          } else if (currentLine.startsWith("Czero")) {
            delay(2000);
            servoC.write(degreeToPos(22));
            delay(2000);
          }
          else if (currentLine.startsWith("Dten")) {
            delay(2000);
            Serial.println("ten");
            servoD.write(degreeToPos(60));
            delay(2000);
          } else if (currentLine.startsWith("Dnine")) {
            delay(2000);
            servoD.write(degreeToPos(31));
            Serial.println("nine");
            delay(2000);
          } else if (currentLine.startsWith("Deight")) {
            delay(2000);
            servoD.write(degreeToPos(30));
            Serial.println("eight");
            delay(2000);
          } else if (currentLine.startsWith("Dseven")) {
            delay(2000);
            servoD.write(degreeToPos(29));
            delay(2000);
          } else if (currentLine.startsWith("Dsix")) {
            delay(2000);
            servoD.write(degreeToPos(28));
            delay(2000);
          } else if (currentLine.startsWith("Dfive")) {
            delay(2000);
            servoD.write(degreeToPos(27));
            delay(2000);
          } else if (currentLine.startsWith("Dfour")) {
            delay(2000);
            servoD.write(degreeToPos(26));
            delay(2000);
          } else if (currentLine.startsWith("Dthree")) {
            delay(2000);
            servoD.write(degreeToPos(25));
            delay(2000);  
          } else if (currentLine.startsWith("Dtwo")) {
            delay(2000);
            servoD.write(degreeToPos(24));
            delay(2000);
          } else if (currentLine.startsWith("Done")) {
            delay(2000);
            servoD.write(degreeToPos(23));
            delay(2000);
          } else if (currentLine.startsWith("Dzero")) {
            delay(2000);
            servoD.write(degreeToPos(22));
            delay(2000);
          }

          currentLine = ""; // Clear the line for the next command
          break; // Break out of the while loop
        }
      }
    }
    
    client.stop(); // Close the connection
    Serial.println("Client disconnected.");
  }
}

float degreeToPos(float deg) {
  return deg/1.5;
}

void moveServo(servo servoX, ){





  
  if (currentLine.startsWith("Aten")) {
    delay(2000);
    Serial.println("ten");
    servoA.write(degreeToPos(60));
    delay(2000);
  } else if (currentLine.startsWith("Anine")) {
    delay(2000);
    servoA.write(degreeToPos(31));
    Serial.println("nine");
    delay(2000);
  } else if (currentLine.startsWith("Aeight")) {
    delay(2000);
    servoA.write(degreeToPos(30));
    Serial.println("eight");
    delay(2000);
  } else if (currentLine.startsWith("Aseven")) {
    delay(2000);
    servoA.write(degreeToPos(29));
    delay(2000);
  } else if (currentLine.startsWith("Asix")) {
    delay(2000);
    servoA.write(degreeToPos(28));
    delay(2000);
  } else if (currentLine.startsWith("Afive")) {
    delay(2000);
    servoA.write(degreeToPos(27));
    delay(2000);
  } else if (currentLine.startsWith("Afour")) {
    delay(2000);
    servoA.write(degreeToPos(26));
    delay(2000);
  } else if (currentLine.startsWith("Athree")) {
    delay(2000);
    servoA.write(degreeToPos(25));
    delay(2000);  
  } else if (currentLine.startsWith("Atwo")) {
    delay(2000);
    servoA.write(degreeToPos(24));
    delay(2000);
  } else if (currentLine.startsWith("Aone")) {
    delay(2000);
    servoA.write(degreeToPos(23));
    delay(2000);
  } else if (currentLine.startsWith("Azero")) {
    delay(2000);
    servoA.write(degreeToPos(22));
    delay(2000);
  }
}