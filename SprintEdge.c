#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>  // Biblioteca para o sensor DHT22

// Configurações do Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* passwordWiFi = "";

// Configurações do MQTT (HiveMQ ou outro broker)
const char* broker = "mqtt-dashboard.com";
const int port = 1883;  // Porta padrão MQTT
const char* clientId = "clientId-yti4dEeWBf";
const char* mqttUser = "";  // Usuário MQTT (pode ser fictício)
const char* mqttPassword = "";  // Senha MQTT (pode ser fictícia)
const char* topic = "formulaE/telemetry";  // Tópico de telemetria

// Pinagem dos sensores
#define PIN_DHT 12  // Pino de dados do sensor DHT22
#define PIN_POT 34  // Pino analógico do potenciômetro

WiFiClient net;
PubSubClient client(net);  // Corrigido para PubSubClient
DHTesp dht;

void connectWiFi() {
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, passwordWiFi);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" conectado!");
}

void connectMQTT() {
  Serial.print("Conectando ao MQTT...");
  while (!client.connected()) {
    if (client.connect(clientId, mqttUser, mqttPassword)) {
      Serial.println(" conectado ao broker MQTT!");
    } else {
      Serial.print(".");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Configurações iniciais
  connectWiFi();
  client.setServer(broker, port);  // Corrigido para setServer em vez de begin
  connectMQTT();
  
  // Configura o sensor de temperatura DHT22
  dht.setup(PIN_DHT, DHTesp::DHT22);

  // Pino do potenciômetro configurado como entrada
  pinMode(PIN_POT, INPUT);
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  // Leitura da temperatura e umidade do DHT22
  TempAndHumidity data = dht.getTempAndHumidity();
  
  // Verifica se a leitura do sensor DHT22 foi bem-sucedida
  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Erro ao ler o sensor DHT22!");
    return;  // Sai do loop se houver erro
  }

  // Mostra a temperatura e umidade no monitor serial
  float temperature = data.temperature;
  float humidity = data.humidity;
  Serial.print("Temperatura: ");
  Serial.println(temperature);
  Serial.print("Umidade: ");
  Serial.println(humidity);

  // Simular a velocidade do carro lendo o valor do potenciômetro (0 a 4095)
  int potValue = analogRead(PIN_POT);
  int speed = map(potValue, 0, 4095, 0, 250);  // Converte para velocidade de 0 a 250 km/h
  Serial.print("Velocidade: ");
  Serial.println(speed);

  // Simular o nível de bateria
  int batteryLevel = random(20, 100);

  // Criando o payload de telemetria em formato JSON
  String payload = "{";
  payload += "\"temperature\": " + String(temperature) + ",";
  payload += "\"humidity\": " + String(humidity) + ",";  // Adiciona a umidade ao payload
  payload += "\"speed\": " + String(speed) + ",";
  payload += "\"batteryLevel\": " + String(batteryLevel);
  payload += "}";

  Serial.println("Enviando dados de telemetria:");
  Serial.println(payload);

  // Publicando a telemetria no tópico MQTT com QoS 2
  if (client.publish(topic, payload.c_str(), 2)) {
    Serial.println("Dados enviados com sucesso!");
  } else {
    Serial.println("Falha ao enviar dados.");
  }

  delay(5000);  // Envia dados a cada 5 segundos
}
