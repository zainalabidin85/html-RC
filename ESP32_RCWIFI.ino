#include <WiFi.h>
#include <WebServer.h>
#include "html_page.h" // Include the external HTML file

// Replace these with your desired SSID and password
const char* ssid = "rc_UNIMAP";
const char* password = "12345678";

// Define pins for motor driver
const int pwm1 = 26; // PWM for Motor 1
const int dir1 = 25; // Direction for Motor 1
const int pwm2 = 27; // PWM for Motor 2
const int dir2 = 33; // Direction for Motor 2

int pwmSpeed = 128; // Default speed (mid-range)

// Initialize web server
WebServer server(80);

// Motor control functions
void setMotorSpeed(int motor, int speed, int direction) {
  if (motor == 1) {
    digitalWrite(dir1, direction);
    analogWrite(pwm1, speed);
  } else if (motor == 2) {
    digitalWrite(dir2, direction);
    analogWrite(pwm2, speed);
  }
}

void forward() {
  Serial.println("Command Received: Forward");
  setMotorSpeed(1, pwmSpeed, HIGH);
  setMotorSpeed(2, pwmSpeed, HIGH);
}

void reverse() {
  Serial.println("Command Received: Reverse");
  setMotorSpeed(1, pwmSpeed, LOW);
  setMotorSpeed(2, pwmSpeed, LOW);
}

void left() {
  Serial.println("Command Received: Left");
  setMotorSpeed(1, 0, HIGH); // Reduce speed for smoother turn
  setMotorSpeed(2, pwmSpeed, HIGH);
}

void right() {
  Serial.println("Command Received: Right");
  setMotorSpeed(1, pwmSpeed, HIGH);
  setMotorSpeed(2, 0, HIGH); // Reduce speed for smoother turn
}

void stopMotors() {
  Serial.println("Command Received: Stop");
  setMotorSpeed(1, 0, HIGH);
  setMotorSpeed(2, 0, HIGH);
}

// Web server control
void handleControl() {
  if (server.hasArg("cmd")) {
    String cmd = server.arg("cmd");

    if (cmd == "forward") forward();
    else if (cmd == "reverse") reverse();
    else if (cmd == "left") left();
    else if (cmd == "right") right();
    else if (cmd == "stop") stopMotors();
    else if (cmd == "speed" && server.hasArg("value")) {
      pwmSpeed = server.arg("value").toInt(); // Update the speed
      Serial.printf("Speed Updated: %d\n", pwmSpeed);
      server.send(200, "text/plain", String(pwmSpeed)); // Acknowledge speed update
      return;
    }

    // Send feedback for other commands
    server.send(200, "text/plain", cmd);
  }
}

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void setup() {
  // Set motor pins as outputs
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);

  // Initialize motors to stop
  stopMotors();

  // Start Wi-Fi in AP mode
  WiFi.softAP(ssid, password);
  Serial.begin(115200);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Configure web server routes
  server.on("/", handleRoot);
  server.on("/control", handleControl);

  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}
