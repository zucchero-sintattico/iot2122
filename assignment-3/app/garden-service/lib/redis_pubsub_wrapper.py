from threading import Thread
from time import sleep
import json


class RedisPubSubWrapper():
    def __init__(self, database):
        self.database = database
        self.pubsub = self.database.pubsub()
        self.channelMap = dict()
        self._start_subscribe_thread()

    def _start_subscribe_thread(self):
        self.subscribe_thread = Thread(target=self._subscribe_splitter_thread)
        self.subscribe_thread.start()

    def _subscribe_splitter_thread(self):
        while True:
            message = self.pubsub.get_message()
            if message:
                if (message["type"] == "subscribe"):
                    continue
                topic = message["channel"].decode()
                data = json.loads(message["data"].decode())
                self.channelMap[topic](data)
            sleep(0.01)

    def subscribe(self, topic, handler):
        self.channelMap[topic] = handler
        self.pubsub.subscribe(topic)
        self.pubsub.get_message()

    def publish(self, topic, message):
        self.database.publish(topic, message)
