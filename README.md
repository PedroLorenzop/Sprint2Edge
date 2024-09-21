
# Projeto de Telemetria IoT com ESP32

Este projeto utiliza o microcontrolador ESP32 para coletar e transmitir dados de sensores (temperatura, velocidade e nível de bateria) via MQTT. A interface de comunicação utiliza um broker MQTT, com visualização de dados através do Node-RED.




## Objetivo
O objetivo do projeto é coletar dados de telemetria de um "carro de corrida" simulado, utilizando o ESP32, um sensor de temperatura/humidade DHT22 e um potenciômetro para simular a velocidade do veículo. Os dados são enviados via protocolo MQTT e visualizados em um dashboard no Node-RED.


## Arquitetura
### Componentes 
    ESP32
    Sensor DHT22 (Temperatura)
    Potenciômetro (Simulação de Velocidade)

### Back-end (MQTT Broker)
    Utiliza o broker público da HiveMQ no endereço mqtt-dashboard.com e porta 1883.

### Front-end (Node-RED)
    Coleta os dados publicados no tópico MQTT e exibe informações sobre a temperatura,  umidade, velocidade e nível de bateria.
    





## Recursos Necessários
### Hardware:
1x ESP32

1x Sensor de Temperatura e Umidade DHT22

1x Potenciômetro

Jumpers e Protoboard para conexão

### Software
Arduino IDE com suporte ao ESP32

Bibliotecas:
WiFi.h (Conexão Wi-Fi)

PubSubClient.h (Protocolo MQTT)

DHTesp.h (Leitura de sensor DHT22)

Broker MQTT (HiveMQ)

Node-RED para visualização dos dados

## Instruções de Uso 
### Configuração do Projeto
#### Instale as bibliotecas necessárias via Arduino IDE.
    Vá em Sketch > Incluir Biblioteca > Gerenciar Bibliotecas.
    Pesquise e instale as bibliotecas mencionadas.

#### Configuração do Broker MQTT
    Utilize o broker MQTT público mqtt-dashboard.com com as seguintes configurações:
        Broker: mqtt-dashboard.com
        Porta: 1883
        Tópico: formulaE/telemetry


#### Configuração do Node-RED
    Instale o Node-RED e adicione um fluxo de MQTT para subscrever ao tópico formulaE/telemetry.
    Configure o dashboard com widgets para exibir os dados recebidos.

## Requisitos
Conexão Wi-Fi: Certifique-se de que o ESP32 esteja conectado a uma rede Wi-Fi com acesso à internet.

Broker MQTT: O broker utilizado no código é o mqtt-dashboard.com, que é um broker público para testes.

Node-RED: Deve estar instalado e configurado para subscrever ao tópico correto.




## Autores

- Enzo Valieres
- Gilherme Barbiero (RM555185)
- Matheus Cantiere (RM558479)
- Pedro de Lorenzo (RM554720)
- Vinicius Castro

