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
          handleCommand(currentLine);

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

void moveServo(Servo &servo, int angle) {
    servo.write(degreeToPos(angle));
    delay(2000); // Remove or reduce if not needed
}

void handleCommand(String command) {
    if (command.startsWith("A")) {
        moveServo(servoA, parseAngle(command));
    } else if (command.startsWith("B")) {
        moveServo(servoB, parseAngle(command));
    } else if (command.startsWith("C")) {
        moveServo(servoC, parseAngle(command));
    } else if (command.startsWith("D")) {
        moveServo(servoD, parseAngle(command));
    }
}

int parseAngle(String command) {
    if (command.endsWith("ten")) return 60;
    if (command.endsWith("nine")) return 31;
    if (command.endsWith("eight")) return 30;
    if (command.endsWith("seven")) return 29;
    if (command.endsWith("six")) return 28;
    if (command.endsWith("five")) return 27;
    if (command.endsWith("four")) return 26;
    if (command.endsWith("three")) return 25;
    if (command.endsWith("two")) return 24;
    if (command.endsWith("one")) return 23;
    if (command.endsWith("zero")) return 22;
    // Add all mappings as needed


}