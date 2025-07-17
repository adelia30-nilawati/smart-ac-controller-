#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";

ESP8266WebServer server(80);

int acPin = D1;

void handleRoot() {
  server.send(200, "text/html", "<h1>Kontrol AC</h1><p><a href='/on'>Nyalakan</a> | <a href='/off'>Matikan</a></p>");
}

void handleOn() {
  digitalWrite(acPin, HIGH);
  server.send(200, "text/html", "<p>AC Dinyalakan!</p><a href='/'>Kembali</a>");
}

void handleOff() {
  digitalWrite(acPin, LOW);
  server.send(200, "text/html", "<p>AC Dimatikan!</p><a href='/'>Kembali</a>");
}

void setup() {
  Serial.begin(115200);
  pinMode(acPin, OUTPUT);
  digitalWrite(acPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Tersambung! Alamat IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
  Serial.println("Server web dimulai");
}

void loop() {
  server.handleClient();
}
