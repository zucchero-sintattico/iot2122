import redis, serial
from threading import Thread
from time import sleep
from redis_pubsub_wrapper import RedisPubSubWrapper

 
db = redis.Redis("localhost")
pubsub = RedisPubSubWrapper(db)

def update_strategy_handler(message):
    print(f"Update strategy : {message}")

def update_status_handler(message):
    print(f"Update status : {message}")

def serial_loop():
    connection = serial.Serial(port = 'COM3', baudrate = 9600)
    while True:
        message = connection.readline()
        message_type, content = message.split(":")

if __name__ == '__main__':
    pubsub.subscribe(topic = "update-strategy", handler = update_strategy_handler)
    pubsub.subscribe(topic = "update-status", handler = update_status_handler)
    #serial_loop()
    while True:
        pubsub.publish("update-strategy", "test")
        sleep(.5)
        pubsub.publish("update-status", "test")
        sleep(.5)