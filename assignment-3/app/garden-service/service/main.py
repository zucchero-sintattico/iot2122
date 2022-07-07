import paho.mqtt.client as mqtt
import redis

db = redis.Redis("redis")

db.set("counter", 0)


def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_message(client, userdata, msg):
    print("Message received: " + str(msg.payload), flush=True)


if __name__ == '__main__':
    try:
        client = mqtt.Client()
        client.on_subscribe = on_subscribe
        client.on_message = on_message
        client.connect("broker-mqtt")
        client.subscribe('#', qos=1)
        client.loop_forever()
    except Exception as exception:
        print('connect to client error')
        print(exception)