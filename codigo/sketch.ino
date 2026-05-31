#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqttServer = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

DHTesp dht;

#define DHTPIN 15

#define RED 25
#define GREEN 26
#define BLUE 27

void setup() {

  Serial.begin(115200);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  dht.setup(DHTPIN, DHTesp::DHT22);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando WiFi...");
  }

  Serial.println("WiFi conectado");

  client.setServer(mqttServer, 1883);
}

void reconnect() {

  while (!client.connected()) {

    Serial.println("Conectando MQTT...");

    if (client.connect("AmandaESP32")) {

      Serial.println("MQTT conectado");

    } else {

      delay(2000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  TempAndHumidity data = dht.getTempAndHumidity();

  float temperatura = data.temperature;
  float umidade = data.humidity;

  int co2 = random(400, 1200);

  int pm25 = random(10, 100);

  client.publish("amanda/temperatura", String(temperatura).c_str());
  client.publish("amanda/umidade", String(umidade).c_str());
  client.publish("amanda/co2", String(co2).c_str());
  client.publish("amanda/pm25", String(pm25).c_str());

  Serial.println("Dados enviados MQTT");

  if (co2 < 700) {

    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);

  } else if (co2 < 1000) {

    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);

  } else {

    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);
  }

  delay(5000);
}
