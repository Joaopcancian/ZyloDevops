# Zylo- Sistema de Alerta Climático IoT

Sistema embarcado com ESP32, sensores ambientais e comunicação MQTT, integrando um painel Node-RED para visualização de temperatura e umidade em tempo real.

---

## 📅 Requisitos

* ESP32 DevKit
* Sensor DHT22 (Temperatura/Umidade)
* 2 LEDs (vermelho, azul)
* Resistor de 1k para cada LED
* Display LCD 20x4 com módulo I2C

---

## 📒 Bibliotecas Necessárias (Arduino IDE)

1. WiFi
2. PubSubClient
3. DHTesp
4. LiquidCrystal\_I2C

Instale em:

```
Sketch > Include Library > Manage Libraries...
```

---

## 🚀 Execução do Projeto

### 1. ESP32

* Copie o código para o Arduino IDE
* Configure a placa: "ESP32 Dev Module"
* Configure a porta: Tools > Port
* Carregue o sketch
* Abra o Serial Monitor (115200 baud)
![ESP-32](esp32.png)
### 2. Node-RED

* Inicie o Node-RED: `node-red`
* Acesse: `http://localhost:1880`
* Instale a paleta `node-red-dashboard` via Menu > Manage Palette
* Importe o `flow.json` de `node-red/`
```JSON
[
    {
        "id": "689920a97860dec2",
        "type": "tab",
        "label": "ClimaRio Dashboard",
        "disabled": false,
        "info": ""
    },
    {
        "id": "5facf8eec857ada1",
        "type": "mqtt in",
        "z": "689920a97860dec2",
        "name": "",
        "topic": "climario/humidity",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "mqtt_broker",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 240,
        "y": 120,
        "wires": [
            [
                "5744c4998a53592f",
                "c3f2381f5f41afb0"
            ]
        ]
    },
    {
        "id": "2c2868c84298df8b",
        "type": "mqtt in",
        "z": "689920a97860dec2",
        "name": "",
        "topic": "climario/temperature",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "mqtt_broker",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 250,
        "y": 260,
        "wires": [
            [
                "a656318abecbfd40",
                "d48dedc0129250a4"
            ]
        ]
    },
    {
        "id": "5744c4998a53592f",
        "type": "debug",
        "z": "689920a97860dec2",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 490,
        "y": 80,
        "wires": []
    },
    {
        "id": "a656318abecbfd40",
        "type": "debug",
        "z": "689920a97860dec2",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 530,
        "y": 240,
        "wires": []
    },
    {
        "id": "c3f2381f5f41afb0",
        "type": "ui_gauge",
        "z": "689920a97860dec2",
        "name": "",
        "group": "7d14c177dc26d1d0",
        "order": 0,
        "width": 0,
        "height": 0,
        "gtype": "gage",
        "title": "Humidade",
        "label": "units",
        "format": "{{value}}",
        "min": 0,
        "max": "100",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "diff": false,
        "className": "",
        "x": 490,
        "y": 160,
        "wires": []
    },
    {
        "id": "d48dedc0129250a4",
        "type": "ui_chart",
        "z": "689920a97860dec2",
        "name": "",
        "group": "7d14c177dc26d1d0",
        "order": 1,
        "width": 0,
        "height": 0,
        "label": "Temperatura",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "",
        "ymax": "",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "3600",
        "cutout": 0,
        "useOneColor": false,
        "useUTC": false,
        "colors": [
            "#1f77b4",
            "#aec7e8",
            "#ff7f0e",
            "#2ca02c",
            "#98df8a",
            "#d62728",
            "#ff9896",
            "#9467bd",
            "#c5b0d5"
        ],
        "outputs": 1,
        "useDifferentColor": false,
        "className": "",
        "x": 530,
        "y": 340,
        "wires": [
            []
        ]
    },
    {
        "id": "mqtt_broker",
        "type": "mqtt-broker",
        "name": "Broker",
        "broker": "broker.hivemq.com",
        "port": "1883",
        "clientid": "",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": 4,
        "keepalive": "60",
        "cleansession": true,
        "autoUnsubscribe": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": ""
    },
    {
        "id": "7d14c177dc26d1d0",
        "type": "ui_group",
        "name": "Temperatura e Humidade",
        "tab": "18dc86070a203f05",
        "order": 1,
        "disp": true,
        "width": 6,
        "collapse": false,
        "className": ""
    },
    {
        "id": "18dc86070a203f05",
        "type": "ui_tab",
        "name": "Home",
        "icon": "dashboard",
        "disabled": false,
        "hidden": false
    }
]
```
* Faça o deploy
* Acesse o dashboard em `http://localhost:1880/ui`

---

## 🔗 Tópicos MQTT Utilizados

| Tópico                 | Descrição              |
| ---------------------- | ---------------------- |
| `climario/temperature` | Temperatura em graus C |
| `climario/humidity`    | Umidade relativa %     |

---

## 📊 Dashboard Node-RED

* **Gráfico de Temperatura:** linha do tempo
* **Gauge de Umidade:** mostrador de ponteiro
* **Status dos LEDs:** automático via ESP32
* **LCD:** exibe os dados no dispositivo

---

## 💡 Observações

* As leituras são feitas a cada 2 segundos
* Temperaturas acima de 30ºC acendem o LED vermelho
* Umidades abaixo de 40% acendem o LED azul

---

## 🌍 Demonstração Visual

---

> Repositório criado para atender aos requisitos mínimos do projeto IoT com ESP32 + Node-RED + MQTT + Dashboard.

---

**Autor:** João Pedro - RM555341
