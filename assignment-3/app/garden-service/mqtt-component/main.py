import redis
import json
import paho.mqtt.client as mqtt
from threading import Thread
from config import Config
from lib.logger import Logger
from lib.garden_repository import GardenRepository

logger = Logger("MQTT Component")
db = redis.Redis(host=Config.redis.host)
garden_repository = GardenRepository(db)
mqtt = mqtt.Client()


def on_mqtt_message(client, userdata, msg):
    data = json.loads(str(msg.payload.decode("utf-8")))
    logger.log(f"Message received: {data}")
    if msg.topic == Config.mqtt.sensorboard and Config.temperature in data and Config.light in data:
        garden_repository.set_temperature(int(data[Config.temperature]))
        garden_repository.set_light(int(data[Config.light]))
        db.publish(
            Config.redis.sensorboard,
            json.dumps({
                Config.temperature: data[Config.temperature],
                Config.light: data[Config.light]
            })
        )


def redis_listener_thread():
    pubsub = db.pubsub()
    pubsub.subscribe(Config.redis.status)
    while True:
        message = pubsub.get_message()
        if message and message["type"] == "message":
            mqtt.publish(Config.mqtt.status, message["data"].decode("utf-8"))


if __name__ == '__main__':
    try:
        # create thread
        thread = Thread(target=redis_listener_thread)
        thread.start()

        # connect to mqtt broker
        mqtt.on_message = on_mqtt_message
        mqtt.connect(Config.mqtt.host)
        mqtt.subscribe(Config.mqtt.sensorboard, qos=2)
        mqtt.loop_forever()
    except Exception as exception:
        print('connect to client error')
        print(exception)
