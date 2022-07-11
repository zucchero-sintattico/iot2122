import paho.mqtt.client as mqtt
import redis
import json
from config import Topic

db = redis.Redis(host='localhost')
mqtt = mqtt.Client()

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_message(client, userdata, msg):
    data = json.loads(str(msg.payload.decode("utf-8")))
    if msg.topic == Topic.sensorboard and "temperature" in data and "light" in data:
        db.set("temperature", data["temperature"])
        db.set("light", data["light"])


if __name__ == '__main__':
    try:
        mqtt.on_subscribe = on_subscribe
        mqtt.on_message = on_message
        mqtt.connect("localhost")
        mqtt.subscribe(Topic.sensorboard, qos=2)
        mqtt.loop_forever()
    except Exception as exception:
        print('connect to client error')
        print(exception)