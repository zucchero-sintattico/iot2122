import redis
from threading import Thread
from time import sleep
from redis_pubsub_wrapper import RedisPubSubWrapper

 
db = redis.Redis("redis")
pubsub = RedisPubSubWrapper(db)



if __name__ == '__main__':
    pass