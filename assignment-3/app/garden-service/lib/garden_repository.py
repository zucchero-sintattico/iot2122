import redis


class Status:

    ALARM = Status("ALARM")
    AUTO = Status("AUTO")
    MANUAL = Status("MANUAL")

    @staticmethod
    def fromString(status):
        if status == "ALARM":
            return Status.ALARM
        elif status == "AUTO":
            return Status.AUTO
        else:
            return Status.MANUAL

    def __init__(self, string_status):
        self.string_status = string_status

    def toString(self):
        return self.string_status


class GardenRepository():

    def __init__(self, db: redis.Redis):
        self.db = db

    """
    General Status
    """

    def get_status(self):
        return Status.fromString(self.db.get("status"))

    def set_status(self, status: Status):
        self.db.set("status", status.toString())

    """
    Sensorboard Status
    """

    def get_temperature(self):
        return int(self.db.get("temperature"))

    def set_temperature(self, value: int):
        self.db.set("temperature", str(value))

    def get_light(self):
        return int(self.db.get("light"))

    def set_light(self, value: int):
        self.db.set("light", str(value))

    """
    Controller Status
    """

    def get_led_1_value(self):
        return int(self.db.get("led1"))

    def set_led_1_value(self, value: int):
        self.db.set("led1", str(value))

    def get_led_2_value(self):
        return int(self.db.get("led2"))

    def set_led_2_value(self, value: int):
        self.db.set("led2", str(value))

    def get_led_3_value(self):
        return int(self.db.get("led3"))

    def set_led_3_value(self, value: int):
        self.db.set("led3", str(value))

    def get_led_4_value(self):
        return int(self.db.get("led4"))

    def set_led_4_value(self, value: int):
        self.db.set("led4", str(value))

    def get_irrigation_speed(self):
        return int(self.db.get("irrigation_speed"))

    def set_irrigation_speed(self, value: int):
        self.db.set("irrigation_speed", str(value))

    def get_irrigator_open(self):
        return bool(self.db.get("irrigator_open"))

    def set_irrigator_open(self, value: bool):
        self.db.set("irrigator_open", str(value))
