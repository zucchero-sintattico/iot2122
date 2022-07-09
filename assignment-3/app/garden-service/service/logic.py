import redis

class ServerLogic:

    def setNewLight(self, light):
        self.light = light

    def setTemperature(self, temperature):
        self.temperature = temperature