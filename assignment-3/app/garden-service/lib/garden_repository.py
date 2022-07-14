import redis, json
from enum import Enum


class Status(Enum):

    ALARM = "ALARM"
    AUTO = "AUTO"
    MANUAL = "MANUAL"

    @staticmethod
    def fromString(status):
        if status == "ALARM":
            return Status.ALARM
        elif status == "AUTO":
            return Status.AUTO
        else:
            return Status.MANUAL

    def toString(self):
        return self.value


class IrrigatorStatus(Enum):

    READY = "READY"
    OPEN = "OPEN"
    CLOSED = "CLOSED"

    @staticmethod
    def fromString(status):
        if status == "READY":
            return IrrigatorStatus.READY
        elif status == "OPEN":
            return IrrigatorStatus.OPEN
        else:
            return IrrigatorStatus.CLOSED

    def toString(self):
        return self.value


class GardenRepository():

    def __init__(self, db: redis.Redis):
        self.db = db
        if self.db.get(RedisKeys.STATUS) is None:
            self.set_status(Status.AUTO)
        if self.db.get(RedisKeys.TEMPERATURE) is None:
            self.set_temperature(0)
        if self.db.get(RedisKeys.LIGHT) is None:
            self.set_light(0)
        if self.db.get(RedisKeys.LED_1) is None:
            self.set_led_1_value(0)
        if self.db.get(RedisKeys.LED_2) is None:
            self.set_led_2_value(0)
        if self.db.get(RedisKeys.LED_3) is None:
            self.set_led_3_value(0)
        if self.db.get(RedisKeys.LED_4) is None:
            self.set_led_4_value(0)
        if self.db.get(RedisKeys.IRRIGATION_SPEED) is None:
            self.set_irrigation_speed(0)
        if self.db.get(RedisKeys.IRRIGATOR_STATUS) is None:
            self.set_irrigator_status(IrrigatorStatus.READY)

    """
    General Status
    """

    def get_status(self):
        return Status.fromString(self.db.get(RedisKeys.STATUS).decode())

    def set_status(self, status: Status):
        self.db.set(RedisKeys.STATUS, status.toString())

    """
    Sensorboard Status
    """

    def get_temperature(self):
        return int(self.db.get(RedisKeys.TEMPERATURE).decode())

    def set_temperature(self, value: int):
        self.db.set(RedisKeys.TEMPERATURE, str(value))

    def get_light(self):
        return int(self.db.get(RedisKeys.LIGHT).decode())

    def set_light(self, value: int):
        self.db.set(RedisKeys.LIGHT, str(value))

    """
    Controller Status
    """

    def get_led_1_value(self):
        return int(self.db.get(RedisKeys.LED_1).decode())

    def set_led_1_value(self, value: int):
        self.db.set(RedisKeys.LED_1, str(value))

    def get_led_2_value(self):
        return int(self.db.get(RedisKeys.LED_2).decode())

    def set_led_2_value(self, value: int):
        self.db.set(RedisKeys.LED_2, str(value))

    def get_led_3_value(self):
        return int(self.db.get(RedisKeys.LED_3).decode())

    def set_led_3_value(self, value: int):
        self.db.set(RedisKeys.LED_3, str(value))

    def get_led_4_value(self):
        return int(self.db.get(RedisKeys.LED_4).decode())

    def set_led_4_value(self, value: int):
        self.db.set(RedisKeys.LED_4, str(value))

    def get_irrigation_speed(self):
        return int(self.db.get(RedisKeys.IRRIGATION_SPEED).decode())

    def set_irrigation_speed(self, value: int):
        self.db.set(RedisKeys.IRRIGATION_SPEED, str(value))

    def get_irrigator_status(self):
        return IrrigatorStatus.fromString(self.db.get(RedisKeys.IRRIGATOR_STATUS).decode())

    def set_irrigator_status(self, status: IrrigatorStatus):
        self.db.set(RedisKeys.IRRIGATOR_STATUS, status.toString())


class RedisKeys():

    STATUS = "status"
    TEMPERATURE = "temperature"
    LIGHT = "light"
    LED_1 = "led1"
    LED_2 = "led2"
    LED_3 = "led3"
    LED_4 = "led4"
    IRRIGATION_SPEED = "irrigation_speed"
    IRRIGATOR_STATUS = "irrigator_status"