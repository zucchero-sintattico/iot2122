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
        light = int(data["light"])  # 0 - 7
        if light < 5:
            strategy["led1"] = 1
            strategy["led2"] = 1
            strategy["led3"] = 4 - light
            strategy["led4"] = 4 - light
        else:
            strategy["led1"] = 0
            strategy["led2"] = 0
            strategy["led3"] = 0
            strategy["led4"] = 0
        strategy["irrigator_speed"] = temperature
        return strategy

    def calculate_status(data):
        temperature = int(data["temperature"]) + 1  # 0 - 4 --> 1 - 5
        if temperature == 5 and not db.get('irrigator_open') == '0':
            return Status.ALARM
        else:
            return garden_repository.get_status()

    def publish_strategy(strategy):
        pubsub.publish("update-strategy", json.dumps(strategy))

    def save_status_and_publish_if_different(status):
        if (status != garden_repository.get_status()):
            garden_repository.set_status(status)
            pubsub.publish("update-status", status.toString())

    data = unpack_message(message)
    logger.log(f"Received new sensorboard values: {data}")
    strategy = calculate_strategy(data)
    logger.log(f"Calculated strategy: {strategy}")
    status = calculate_status(data)
    logger.log(f"Calculated status: {status}")
    publish_strategy(strategy)
    save_status_and_publish_if_different(status)


if __name__ == '__main__':
    garden_repository.set_status(Status.AUTO)
    pubsub.subscribe("update-sensorboard", on_new_sensorboard_values)
