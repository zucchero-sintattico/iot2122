import redis
from redis_pubsub_wrapper import RedisPubSubWrapper

db = redis.Redis("localhost")
pubsub = RedisPubSubWrapper(db)


def on_new_sensorboard_values(message):
    def unpack_message(msg):
        pass

    def calculate_strategy(data):
        pass
    data = unpack_message(message)
    strategy, status = calculate_strategy(data)
    pubsub.publish("update-strategy", strategy)
    pubsub.publish("update-status", status)


if __name__ == '__main__':
    pubsub.subscribe("update-sensorboard", on_new_sensorboard_values)
