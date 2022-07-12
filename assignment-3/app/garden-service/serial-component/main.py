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
    connection = serial.Serial(port = '/dev/ttyS4', baudrate = 9600)
    while True:
        message = connection.readline().decode()
        if message.startswith("STATUS"):
            print(f"Message from serial: {message}")
            content = message.split(":")[1]


if __name__ == '__main__':
    pubsub.subscribe(topic = "update-strategy", handler = update_strategy_handler)
    pubsub.subscribe(topic = "update-status", handler = update_status_handler)
    serial_loop()