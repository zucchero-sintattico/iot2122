import redis
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

    """
    General Status
    """

    def get_status(self):
        return Status.fromString(self.db.get("status").decode())

    def set_status(self, status: Status):
        self.db.set("status", status.toString())

    """
    Sensorboard Status
    """

    def get_temperature(self):
        return int(self.db.get("temperature").decode())

    def set_temperature(self, value: int):
        self.db.set("temperature", str(value))

    def get_light(self):
        return int(self.db.get("light").decode())

    def set_light(self, value: int):
        self.db.set("light", str(value))

    """
    Controller Status
    """

    def get_led_1_value(self):
        return int(self.db.get("led1").decode())

    def set_led_1_value(self, value: int):
        self.db.set("led1", str(value))

    def get_led_2_value(self):
        return int(self.db.get("led2").decode())

    def set_led_2_value(self, value: int):
        self.db.set("led2", str(value))

    def get_led_3_value(self):
        return int(self.db.get("led3").decode())

    def set_led_3_value(self, value: int):
        self.db.set("led3", str(value))

    def get_led_4_value(self):
        return int(self.db.get("led4").decode())

    def set_led_4_value(self, value: int):
        self.db.set("led4", str(value))

    def get_irrigation_speed(self):
        return int(self.db.get("irrigation_speed").decode())

    def set_irrigation_speed(self, value: int):
        self.db.set("irrigation_speed", str(value))

    def get_irrigator_status(self):
        return IrrigatorStatus.fromString(self.db.get("irrigator_status").decode())

    def set_irrigator_status(self, status: IrrigatorStatus):
        self.db.set("irrigator_status", status.toString())
