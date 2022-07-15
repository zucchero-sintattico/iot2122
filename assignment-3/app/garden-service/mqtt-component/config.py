class Config:
    class mqtt:
        host = "mosquitto"
        sensorboard = "smart-garden/sensorboard"
        status = "smart-garden/status"
    
    class redis:
        host = "redis"
        sensorboard = "update-sensorboard"
        status = "update-status"

    temperature = "temperature"
    light = "light"