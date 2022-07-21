import redis
import serial
import json
import random
from threading import Thread
from time import sleep
from lib.redis_pubsub_wrapper import RedisPubSubWrapper
from lib.logger import Logger
from lib.garden_repository import GardenRepository, IrrigatorStatus
from lib.pubsub_repository import PubSubRepository

logger = Logger("Serial Component")
db = redis.Redis("localhost")
pubsub = PubSubRepository(db)
garden_repository = GardenRepository(db)
connection = serial.Serial(port='COM8', baudrate=9600)


def update_strategy_handler(strategy):
    logger.log(f"New strategy received: {strategy}")
    strategy_message = f"UPDATE:{strategy['led1']},{strategy['led2']},{strategy['led3']},{strategy['led4']},{strategy['irrigator_speed']}\n"
    logger.log(f"Sending strategy = {strategy_message}")
    connection.write(strategy_message.encode())
    if strategy["open_irrigator"]:
        command = f"COMMAND:OPEN_IRRIGATOR\n"
        logger.log(f"Sending command = {command}")
        connection.write(command.encode())


def update_status_handler(data):
    status_message = f"STATUS_CHANGE:{data.get('status')}\n"
    logger.log(f"Sending status change = {status_message}")
    connection.write(status_message.encode())


def serial_loop():

    def update_values_to_db(l1, l2, l3, l4, irrigator_status, irrigator_speed):
        garden_repository.set_led_1_value(l1)
        garden_repository.set_led_2_value(l2)
        garden_repository.set_led_3_value(l3)
        garden_repository.set_led_4_value(l4)
        garden_repository.set_irrigator_status(irrigator_status)
        garden_repository.set_irrigation_speed(irrigator_speed)

    def notify_new_values(l1, l2, l3, l4, irrigator_status: IrrigatorStatus, irrigator_speed):
        pubsub.publish_new_controller_values({
            "led1": l1,
            "led2": l2,
            "led3": l3,
            "led4": l4,
            "irrigator_status": irrigator_status.toString(),
            "irrigation_speed": irrigator_speed
        })

    while True:
        message = connection.readline()
        try:
            message = message.decode()
            message = message.strip().replace("\n", "")
        except:
            continue
        if not message.startswith("STATUS"):
            logger.log(f"Received message = {message}")
        else:
            content = message.split(":")[1]
            l1, l2, l3, l4, status, irrigator_speed = content.split(
                ",")
            irrigator_status = None
            if status == "0":
                irrigator_status = IrrigatorStatus.READY
            elif status == "1":
                irrigator_status = IrrigatorStatus.OPEN
            else:
                irrigator_status = IrrigatorStatus.CLOSED

            update_values_to_db(
                l1, l2, l3, l4, irrigator_status, irrigator_speed)
            notify_new_values(
                l1, l2, l3, l4, irrigator_status, irrigator_speed)


if __name__ == '__main__':
    pubsub.set_on_new_strategy_handler(handler=update_strategy_handler)
    pubsub.set_on_new_status_handler(handler=update_status_handler)
    serial_loop()
