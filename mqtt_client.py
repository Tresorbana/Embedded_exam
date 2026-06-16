import serial
import paho.mqtt.client as mqtt

SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE   = 9600
BROKER      = "broker.benax.rw"
TOPIC       = "sensor_bana_emmy_tresor"

ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
client = mqtt.Client()
client.connect(BROKER, 1883, 60)

print("Monitoring temperature...\n")

while True:
    temp = ser.readline().decode().strip()
    print("Temperature:", temp)
    client.publish(TOPIC, temp)