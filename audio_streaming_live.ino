#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Martin";  // Change this
const char* password = "amulya16";  // Change this
String audioURL = "http://192.168.239.40:5454/audio";  // Flask server IP

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
    "<html><body>"
    "<h2>ESP32 Audio Stream</h2>"
    "<audio controls autoplay>"
    "<source src='" + audioURL + "' type='audio/wav'>"  // Streaming Flask audio
    "Your browser does not support the audio element."
    "</audio>"
    "</body></html>"
  );
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
