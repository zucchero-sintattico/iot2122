class Config:
    class mqtt:
        host = "broker-mqtt"
        sensorboard = "smart-garden/sensorboard"
        status = "smart-garden/status"
    
    class redis:
        host = "redis"
        sensorboard = "update-sensorboard"
        status = "update-status"

    temperature = "temperature"
    light = "light"