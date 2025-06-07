#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pino do DHT22
const int DHT_PIN = 9;
DHTesp dhtSensor;

// Wi-Fi
const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);

// LEDs de alerta
#define LED_VERMELHO 26
#define LED_AZUL      27

// LCD I2C (endereço 0x27, 20 colunas × 4 linhas)
LiquidCrystal_I2C lcd(0x27, 20, 4);

unsigned long lastMsg = 0;
const long intervalo  = 2000; // 2 segundos

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando em ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println();
  Serial.println("Wi-Fi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Apenas imprime a mensagem recebida (não altera LEDs neste exemplo)
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop até conectar ao broker MQTT
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
      // Se necessário, inscrever em tópicos aqui:
      // client.subscribe("climario/led/controle");
    } else {
      Serial.print("falha, código=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Inicializa o DHT22
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // Configura pinos dos LEDs
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AZUL, LOW);

  // Inicializa o LCD I2C
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando sistema");
  delay(2000);
  lcd.clear();

  // Conecta à rede Wi-Fi
  setup_wifi();

  // Configura MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > intervalo) {
    lastMsg = now;

    // 1) Leitura do DHT22
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temperatura     = data.temperature;
    float umidade         = data.humidity;

    // 2) Verifica o DHT22
    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("Inicializando DHT");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Inicializando DHT");
      return;
    }

    // 3) Aciona LEDs conforme temperatura e umidade
    digitalWrite(LED_VERMELHO, temperatura > 30.0 ? HIGH : LOW);
    digitalWrite(LED_AZUL,      umidade   < 40.0 ? HIGH : LOW);

    // 4) Publica temperatura no tópico MQTT
    String temp_str = String(temperatura, 1);
    client.publish("climario/temperature", temp_str.c_str());
    Serial.print("Temperatura: ");
    Serial.println(temp_str);

    // 5) Publica umidade no tópico MQTT
    String hum_str = String(umidade, 1);
    client.publish("climario/humidity", hum_str.c_str());
    Serial.print("Umidade: ");
    Serial.println(hum_str);

    // 6) Atualiza o LCD com temperatura e umidade
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura, 1);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umidade, 1);
    lcd.print(" %");
  }
}
