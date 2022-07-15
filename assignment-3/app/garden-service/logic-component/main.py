import redis
import json
from lib.garden_repository import GardenRepository, Status, IrrigatorStatus
from lib.pubsub_repository import PubSubRepository
from lib.logger import Logger

logger = Logger("Logic Component")

db = redis.Redis("redis")
pubsub = PubSubRepository(db)
garden_repository = GardenRepository(db)


def on_new_sensorboard_values(message):
    def calculate_strategy(data):
        strategy = dict()
        temperature = int(data["temperature"])  # 1 - 5
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
        if light < 2 and garden_repository.get_irrigator_status() == IrrigatorStatus.READY:
            strategy["open_irrigator"] = True
        else:
            strategy["open_irrigator"] = False
        strategy["irrigator_speed"] = temperature
        return strategy

    def calculate_status(data):
        temperature = int(data["temperature"]) + 1  # 0 - 4 --> 1 - 5
        if temperature == 5 and not db.get('irrigator_open') == '0':
            return Status.ALARM
        else:
            return garden_repository.get_status()

    def publish_strategy(strategy):
        pubsub.publish_new_strategy(strategy)

    def save_status_and_publish_if_different(status):
        if (status != garden_repository.get_status()):
            garden_repository.set_status(status)
            pubsub.publish_new_status(status)

    # Do not calculate the strategy if the system is not on AUTO status
    if garden_repository.get_status() == Status.ALARM or garden_repository.get_status() == Status.MANUAL:
        return

    data = message
    logger.log(f"Received new sensorboard values: {data}")
    strategy = calculate_strategy(data)
    logger.log(f"Calculated strategy: {strategy}")
    status = calculate_status(data)
    logger.log(f"Calculated status: {status}")
    publish_strategy(strategy)
    save_status_and_publish_if_different(status)


if __name__ == '__main__':
    garden_repository.set_status(Status.AUTO)
    pubsub.set_on_new_sensorboard_values_handler(on_new_sensorboard_values)
