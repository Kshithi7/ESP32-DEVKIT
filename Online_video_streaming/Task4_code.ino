#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "<Your WiFi SSID>";  // Change this 
const char* password = "<WiFi password>";  // Change this
String videoURL = "<URL of laptop obtained after running Flask server>";  // Update with laptop's IP

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
