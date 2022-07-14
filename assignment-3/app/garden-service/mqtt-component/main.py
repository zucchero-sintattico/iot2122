import redis
import json
import paho.mqtt.client as mqtt
from threading import Thread
from config import Config
from lib.logger import Logger
from lib.garden_repository import GardenRepository
from lib.pubsub_repository import PubSubRepository

logger = Logger("MQTT Component")
db = redis.Redis(host=Config.redis.host)
pubsub = PubSubRepository(db)
garden_repository = GardenRepository(db)
mqtt = mqtt.Client()


def on_mqtt_message(client, userdata, msg):
    data = json.loads(str(msg.payload.decode("utf-8")))
    logger.log(f"Message received: {data}")
    if msg.topic == Config.mqtt.sensorboard and Config.temperature in data and Config.light in data:
        garden_repository.set_temperature(int(data[Config.temperature]))
        garden_repository.set_light(int(data[Config.light]))
        pubsub.publish_new_sensorboard_values({
            Config.temperature: data[Config.temperature],
            Config.light: data[Config.light]
        })


def on_new_status(message):
    status = message["status"]
    mqtt.publish(Config.mqtt.status, status)


if __name__ == '__main__':
    try:
        pubsub.set_on_new_status_handler(on_new_status)

        # connect to mqtt broker
        mqtt.on_message = on_mqtt_message
        mqtt.connect(Config.mqtt.host)
        mqtt.subscribe(Config.mqtt.sensorboard, qos=2)
        mqtt.loop_forever()
    except Exception as exception:
        print('connect to client error')
        print(exception)
