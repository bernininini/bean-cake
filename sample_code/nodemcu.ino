#include <ESP8266WiFi.h>

const char* ssid = "ESP32_Joystick_AP";
const char* password = "12345678";

WiFiServer server(3333);
WiFiClient client;
String inputBuffer = "";

void setup() {
  Serial.begin(115200); 

  WiFi.softAP(ssid, password);
  Serial.println("ESP8266: AP Started");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  Serial.println("Waiting for client...");
}

void loop() {
  if (!client || !client.connected()) {
    client = server.available();
    if (client) Serial.println("Client connected!");
  }

  while (client && client.connected() && client.available()) {
    char c = client.read();
    if (c == '\n') {
      parseJoystickData(inputBuffer);
      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }
}

void parseJoystickData(String data) {
  data.trim();
  int indexes[3];
  indexes[0] = data.indexOf(',');
  indexes[1] = data.indexOf(',', indexes[0] + 1);
  indexes[2] = data.indexOf(',', indexes[1] + 1);

  if (indexes[0] == -1 || indexes[1] == -1 || indexes[2] == -1) {
    Serial.println("Invalid data: " + data);
    return;
  }

  int j1_x = data.substring(0, indexes[0]).toInt();
  int j1_y = data.substring(indexes[0] + 1, indexes[1]).toInt();
  int j2_x = data.substring(indexes[1] + 1, indexes[2]).toInt();
  int j2_y = data.substring(indexes[2] + 1).toInt();

  Serial.print("Joystick 1 X: ");
  Serial.print(j1_x);
  Serial.print(" | Y: ");
  Serial.print(j1_y);
  Serial.print(" || Joystick 2 X: ");
  Serial.print(j2_x);
  Serial.print(" | Y: ");
  Serial.println(j2_y);

  Serial.print(data);
  Serial.print("\n");
}
