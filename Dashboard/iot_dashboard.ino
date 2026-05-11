#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "html.h"

const char* ssid     = "Heidelberg";
const char* password = "Githib123";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 40) {
      Serial.println("\nFailed to connect Kawawa ka naman. Restarting...");
      delay(2000); // delay 2sec
      ESP.restart();
    }
  }

  Serial.println("\nWaypayy iz Connected!");
  Serial.print("IP Address: http://"); Serial.println(WiFi.localIP());

  // Serve the dashboard HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  // 404
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Alaws Server Bossing :< ");
  });

  server.begin();
  Serial.println("Web server started napo Master!!");
}

void loop() {
  //LOOP
}
