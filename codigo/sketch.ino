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

void apagarLED() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void acenderVerde() {
  apagarLED();
  digitalWrite(GREEN, HIGH);
}

void acenderAmarelo() {
  apagarLED();
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
}

void acenderVermelho() {
  apagarLED();
  digitalWrite(RED, HIGH);
}

void setup() {

  Serial.begin(115200);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  apagarLED();

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

      Serial.println("Falha MQTT. Tentando novamente...");
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

  Serial.println("================================");

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  Serial.print("Umidade: ");
  Serial.println(umidade);

  Serial.print("CO2: ");
  Serial.println(co2);

  Serial.print("PM2.5: ");
  Serial.println(pm25);

  if (co2 < 700) {

    Serial.println("Qualidade do ar: BOA");
    Serial.println("LED VERDE");

    acenderVerde();

  } else if (co2 < 1000) {

    Serial.println("Qualidade do ar: MODERADA");
    Serial.println("LED AMARELO");

    acenderAmarelo();

  } else {

    Serial.println("Qualidade do ar: RUIM");
    Serial.println("LED VERMELHO");

    acenderVermelho();
  }

  Serial.println("Dados enviados MQTT");
  Serial.println("================================");

  delay(5000);
}
