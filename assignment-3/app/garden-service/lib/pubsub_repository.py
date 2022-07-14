from redis import Redis
from lib.redis_pubsub_wrapper import RedisPubSubWrapper
from lib.garden_repository import Status
import json


class PubSubRepository:

    class config:
        new_strategy_channel = "update-strategy"
        new_status_channel = "update-status"
        new_sensorboard_values_channel = "update-sensorboard"
        new_controller_values_channel = "update-controller"

    def __init__(self, db: Redis):
        self.db = db
        self.pubsub = RedisPubSubWrapper(self.db)

    # Strategy

    def publish_new_strategy(self, strategy: dict):
        self.pubsub.publish(
            topic=self.config.new_strategy_channel,
            message=json.dumps(strategy)
        )

    def set_on_new_strategy_handler(self, handler):
        self.pubsub.subscribe(
            topic=self.config.new_strategy_channel,
            handler=handler
        )

    # Status

    def publish_new_status(self, status: Status):
        self.pubsub.publish(
            topic=self.config.new_status_channel,
            message=json.dumps({"status": status.value})
        )

    def set_on_new_status_handler(self, handler):
        self.pubsub.subscribe(
            topic=self.config.new_status_channel,
            handler=handler
        )

    # Sensorboard

    def publish_new_sensorboard_values(self, data: dict):
        self.pubsub.publish(
            topic=self.config.new_sensorboard_values_channel,
            message=json.dumps(data)
        )

    def set_on_new_sensorboard_values_handler(self, handler):
        self.pubsub.subscribe(
            topic=self.config.new_sensorboard_values_channel,
            handler=handler
        )

    # Controller

    def publish_new_controller_values(self, data: dict):
        self.pubsub.publish(
            topic=self.config.new_controller_values_channel,
            message=json.dumps(data)
        )

    def set_on_new_controller_values_handler(self, handler):
        self.pubsub.subscribe(
            topic=self.config.new_controller_values_channel,
            handler=handler
        )
