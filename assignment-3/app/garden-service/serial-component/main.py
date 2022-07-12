import redis, serial, json, random
from threading import Thread
from time import sleep
from redis_pubsub_wrapper import RedisPubSubWrapper

 
db = redis.Redis("localhost")
pubsub = RedisPubSubWrapper(db)
connection = serial.Serial(port = '/dev/ttyS8', baudrate = 9600)

def update_strategy_handler(message):
    strategy = json.loads(message)
    print(f"New strategy received: {strategy}")
    strategy_message = f"UPDATE:{strategy['led1']},{strategy['led2']},{strategy['led3']},{strategy['led4']},{strategy['irrigator_speed']}\n"
    print(f"Strategy message = {strategy_message}")
    connection.write(strategy_message.encode())

def update_status_handler(message):
    status_message = f"STATUS_CHANGE:{message}\n"
    connection.write(status_message.encode())

def serial_loop():

    def update_values_to_db(l1, l2, l3, l4, irrigator_open, irrigator_speed):
        db.set("led1", l1)
        db.set("led2", l2)
        db.set("led3", l3)
        db.set("led4", l4)
        db.set("irrigator_open", irrigator_open)
        db.set("irrigator_speed", irrigator_speed)

    def notify_new_values(l1, l2, l3, l4, irrigator_open, irrigator_speed):
        pubsub.publish("update-controllerStatus", json.dumps({
                "led1": l1,
                "led2": l2,
                "led3": l3,
                "led4": l4,
                "irrigator_open": irrigator_open,
                "irrigator_speed": irrigator_speed
            }))
            
    while True:
        message = connection.readline()
        try:
            message = message.decode()
            message = message.strip().replace("\n", "")
        except:
            continue
        if message.startswith("STATUS"):
            content = message.split(":")[1]
            print(f"New status received: {content}")
            l1, l2, l3, l4, irrigator_open, irrigator_speed = content.split(",")
            update_values_to_db(l1, l2, l3, l4, irrigator_open, irrigator_speed)
            notify_new_values(l1, l2, l3, l4, irrigator_open, irrigator_speed)

def simulator():
    while True:
        sleep(5)
        update_strategy_handler(json.dumps({
            "led1": random.randint(0, 1),
            "led2": random.randint(0, 1),
            "led3": 4,
            "led4": random.randint(0, 4),
            "irrigator_speed": random.randint(1, 5)
        }))
        
if __name__ == '__main__':
    pubsub.subscribe(topic = "update-strategy", handler = update_strategy_handler)
    pubsub.subscribe(topic = "update-status", handler = update_status_handler)
    Thread(target=simulator).start()
    serial_loop()