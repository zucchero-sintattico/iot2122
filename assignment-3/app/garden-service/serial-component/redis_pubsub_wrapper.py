class RedisPubSubWrapper():
    
    def __init__(self, database: redis.Redis):
        self.database: redis.Redis = database
        self.pubsub = self.database.pubsub()
        self.channelMap = []

    def _start_subscribe_thread():
        self.subscribe_thread = Thread(target=_subscribe_splitter_thread)
        self.subscribe_thread.start()

    def _subscribe_splitter_thread():
        while True:
            message = self.pubsub.get_message()
            if message:
                topic = message.topic
                self.channelMap[topic]()
            sleep(0.01)

    def subscribe(topic: str, handler):
        self.channelMap[topic] = handler
        self.pubsub.subscribe(topic)

    def publish(topic: str, message: str):
        self.database.publish(topic, message)
