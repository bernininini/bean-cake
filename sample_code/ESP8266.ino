//use TX RX to communicate btwn esp and uno

#include <WiFi.h>

const char* ssid = "ESP32_Joystick_AP";
const char* password = "12345678";

const char* server_ip = "192.168.4.1";
const int server_port = 3333;

WiFiClient client;

String inputBuffer = "";

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ESP8266 AP");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to AP");

  while (!client.connect(server_ip, server_port)) {
    Serial.println("Connecting to ESP8266 server...");
    delay(1000);
  }
  Serial.println("Connected to ESP8266 server!");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      Serial.print("Received from Arduino: ");
      Serial.println(inputBuffer);

      client.print(inputBuffer + "\n");
      Serial.println("Sent over WiFi!");

      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }
}

