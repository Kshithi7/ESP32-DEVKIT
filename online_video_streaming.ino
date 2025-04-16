#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Oppo";  // Change this 
const char* password = "navyashree";  // Change this
String videoURL = "http://192.168.25.40:5000/video";  // Update with laptop's IP

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
    "<html><body>"
    "<h2>ESP32 Video Stream</h2>"
    "<img src='" + videoURL + "' width='100%'>"
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
