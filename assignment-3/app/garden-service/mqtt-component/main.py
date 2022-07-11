import paho.mqtt.client as mqtt
from config import Topic

mqtt = mqtt.Client()

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_message(client, userdata, msg):
    match msg.topic:
        case Topic.light: pass # TODO
        case Topic.temperature: pass # TODO


if __name__ == '__main__':
    try:
        mqtt.on_subscribe = on_subscribe
        mqtt.on_message = on_message
        mqtt.connect("broker-mqtt")
        mqtt.subscribe(Topic.light, qos=1)
        mqtt.subscribe(Topic.temperature, qos=1)
        mqtt.loop_forever()
    except Exception as exception:
        print('connect to client error')
        print(exception)