# Arduino Temperature Monitor

Candidate: Bana Emmy Tresor

## System overview

DHT11 sensor → Arduino Uno → USB Serial → PC Python client → MQTT broker → Web UI

## Hardware

| Component       | Connection         |
|-----------------|--------------------|
| DHT11 VCC       | Arduino 5V         |
| DHT11 GND       | Arduino GND        |
| DHT11 DATA      | Arduino D2         |
| LCD I2C VCC     | Arduino 5V         |
| LCD I2C GND     | Arduino GND        |
| LCD I2C SDA     | Arduino A4         |
| LCD I2C SCL     | Arduino A5         |

Add a 10kΩ pull-up resistor between DHT11 DATA and VCC.

## Arduino

- Open `arduino/arduino.ino` in Arduino IDE
- Board: Arduino Uno
- Port: /dev/ttyACM0
- Upload the sketch

## PC client (Ubuntu)

Install dependencies:
```bash
pip3 install pyserial paho-mqtt --break-system-packages
```

Run:
```bash
python3 pc_client/mqtt_client.py
```

## Communication

| Link                  | Protocol        | Details                        |
|-----------------------|-----------------|-------------------------------|
| Arduino → PC          | Serial UART     | /dev/ttyACM0, 9600 baud       |
| PC → MQTT broker      | MQTT TCP        | broker.benax.rw, port 1883    |
| Browser → MQTT broker | MQTT WebSocket  | 157.173.101.159, port 9001    |
| MQTT topic            |                 | sensor_bana_emmy_tresor       |

## Web UI

Hosted on VPS via PM2 at: http://157.173.101.159:8205/ui.html

The UI connects to the MQTT broker via WebSocket and displays
live temperature readings with history.

## VPS

The UI is served using a Python HTTP server managed by PM2:
```bash
pm2 start /home/user205/Exam/Exam/pc_client/serve.py \
  --name temperature-ui --interpreter python3
```
