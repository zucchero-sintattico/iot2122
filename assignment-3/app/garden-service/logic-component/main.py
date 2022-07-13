import redis
import json
from lib.redis_pubsub_wrapper import RedisPubSubWrapper
from lib.garden_repository import GardenRepository, Status
from lib.logger import Logger

logger = Logger("Logic Component")
db = redis.Redis("redis")
pubsub = RedisPubSubWrapper(db)
garden_repository = GardenRepository(db)


def on_new_sensorboard_values(message):
    def unpack_message(msg):
        return json.loads(msg)

    def calculate_strategy(data):
        strategy = dict()
        temperature = int(data["temperature"]) + 1  # 0 - 4 --> 1 - 5
        light = int(data["light"]) + 1  # 0 - 7 --> 1 - 8
        if light < 5:
            strategy["led1"] = 1
            strategy["led2"] = 1
            strategy["led3"] = 5 - light
            strategy["led4"] = 5 - light
        else:
            strategy["led1"] = 0
            strategy["led2"] = 0
            strategy["led3"] = 0
            strategy["led4"] = 0
        strategy["irrigation_speed"] = temperature

    def calculate_status(data):
        temperature = int(data["temperature"]) + 1  # 0 - 4 --> 1 - 5
        if temperature == 5 and not db.get('irrigator_open') == '0':
            return Status.ALARM
        else:
            return garden_repository.get_status()

    def publish_strategy(strategy):
        pubsub.publish("update-strategy", strategy)

    def save_status_and_publish_if_different(status):
        if (status != garden_repository.get_status()):
            garden_repository.set_status(status)
            pubsub.publish("update-status", status)

    data = unpack_message(message)
    strategy = calculate_strategy(data)
    status = calculate_status(data)
    publish_strategy(strategy)
    save_status_and_publish_if_different(status)


if __name__ == '__main__':
    pubsub.subscribe("update-sensorboard", on_new_sensorboard_values)
