# Sistema de Monitoramento Ambiental com IoT e MQTT

Este projeto apresenta um sistema de monitoramento ambiental utilizando Internet das Coisas (IoT), desenvolvido com ESP32, sensor DHT22, LED RGB e protocolo MQTT.

O sistema realiza a leitura da temperatura e da umidade do ambiente por meio do sensor DHT22. Os valores de CO₂ e material particulado PM2.5 são simulados por software devido às limitações da plataforma de simulação utilizada.

Os dados são enviados para um broker MQTT HiveMQ através da conexão Wi-Fi do ESP32, permitindo o monitoramento remoto em tempo real.

## Componentes utilizados

- ESP32
- Sensor DHT22
- LED RGB
- Resistores de 220 Ω

## Softwares e plataformas

- Wokwi
- Arduino IDE
- HiveMQ Web Client
- Lucidchart

## Comunicação MQTT

Tópicos utilizados:

- amanda/temperatura
- amanda/umidade
- amanda/co2
- amanda/pm25

## Funcionamento

1. O ESP32 conecta-se ao Wi-Fi.
2. O ESP32 conecta-se ao broker MQTT.
3. O sensor DHT22 coleta temperatura e umidade.
4. Os valores simulados de CO₂ e PM2.5 são gerados pelo código.
5. Os dados são enviados ao broker MQTT.
6. O LED RGB muda de cor conforme a qualidade do ar simulada.

## Indicação do LED RGB

- Verde: qualidade do ar boa
- Amarelo: qualidade do ar moderada
- Vermelho: qualidade do ar ruim
