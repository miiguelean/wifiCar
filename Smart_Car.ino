#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const int TRIGGER_PIN_1 = 4;
const int ECHO_PIN_1 = 2;

// Definir pines de trigger y eco para el sensor 2
const int TRIGGER_PIN_2 = 23;
const int ECHO_PIN_2 = 22;

//definir el pin del buzzer
const int buzzer = 5;

const char* ssid = "iPhone De Miguel";
const char* password = "tienda26";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(27, OUTPUT); // Motor 1, input 1
  pinMode(26, OUTPUT); // Motor 1, input 2
  pinMode(25, OUTPUT); // Motor 2, input 1
  pinMode(33, OUTPUT); // Motor 2, input 2

  pinMode(buzzer, OUTPUT);

  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/forward", []() {
    digitalWrite(27, HIGH); // Motor 1, input 1
    digitalWrite(26, LOW); // Motor 1, input 2
    digitalWrite(25, HIGH); // Motor 2, input 1
    digitalWrite(33, LOW); // Motor 2, input 2
    server.send(200, "text/html", "<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"0;URL=https://tiendagod.000webhostapp.com/car/control.php\">");
  });


  server.on("/backward", []() {
    digitalWrite(27, LOW); // Motor 1, input 1
    digitalWrite(26, HIGH); // Motor 1, input 2
    digitalWrite(25, LOW); // Motor 2, input 1
    digitalWrite(33, HIGH); // Motor 2, input 2
    server.send(200, "text/html", "<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"0;URL=https://tiendagod.000webhostapp.com/car/control.php\">");
  });

  server.on("/left", []() {
    digitalWrite(27, LOW); // Motor 1, input 1
    digitalWrite(26, HIGH); // Motor 1, input 2
    digitalWrite(25, HIGH); // Motor 2, input 1
    digitalWrite(33, LOW); // Motor 2, input 2
    server.send(200, "text/html", "<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"0;URL=https://tiendagod.000webhostapp.com/car/control.php\">");
  });

  server.on("/stop", []() {
    digitalWrite(27, LOW); // Motor 1, input 1
    digitalWrite(26, LOW); // Motor 1, input 2
    digitalWrite(25, LOW); // Motor 2, input 1
    digitalWrite(33, LOW); // Motor 2, input 2
    server.send(200, "text/html", "<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"0;URL=https://tiendagod.000webhostapp.com/car/control.php\">");
  });

  server.on("/right", []() {
    digitalWrite(27, HIGH); // Motor 1, input 1
    digitalWrite(26, LOW); // Motor 1, input 2
    digitalWrite(25, LOW); // Motor 2, input 1
    digitalWrite(33, HIGH); // Motor 2, input 2
    server.send(200, "text/html", "<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"0;URL=https://tiendagod.000webhostapp.com/car/control.php\">");
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
  
  int distance1 = getDistance(TRIGGER_PIN_1, ECHO_PIN_1);
  int distance2 = getDistance(TRIGGER_PIN_2, ECHO_PIN_2);
  if (distance1 < 25 || distance2 < 20) {
    sendData(1);
    digitalWrite(buzzer, HIGH);
  } else {
    sendData(0);
    digitalWrite(buzzer, LOW);
  }
  delay(300);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

void sendData(int value) {
  HTTPClient http;
  String url = "https://tiendagod.000webhostapp.com/car/insert.php?valor=" + String(value);
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String response = http.getString();
    Serial.println(response);
  }
  http.end();
}