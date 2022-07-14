from time import sleep
import redis
import json
from flask import Flask, request, Response, send_from_directory
from lib.pubsub_repository import PubSubRepository
from lib.garden_repository import GardenRepository, Status, RedisKeys
db = redis.Redis("redis")
app = Flask(__name__)
pubsub = PubSubRepository(db)
garden_repository = GardenRepository(db)


@app.route('/status', methods=['GET'])
def get_status():
    return json.dumps({RedisKeys.STATUS: garden_repository.get_status()}) + "\n"


@app.route('/status', methods=['POST'])
def post_status():
    status = Status.fromString(request.get_data().decode('utf-8'))
    if status == Status.AUTO or status == Status.MANUAL:
        garden_repository.set_status(status)
        pubsub.publish_new_status(status)
        return Response("Status changed\n", mimetype='text/plain', status=200)
    else:
        return Response("Error on status\n", mimetype='text/plain', status=400)


@app.route('/garden-dashboard/<path:path>')
def get_dashboard_files(path):
    return send_from_directory('garden-dashboard', path)


@app.route('/dashboard-status', methods=['GET'])
def get_dashboard_status():

    return Response(
        json.dumps({
            RedisKeys.STATUS: garden_repository.get_status().toString(),
            RedisKeys.TEMPERATURE: garden_repository.get_temperature(),
            RedisKeys.LIGHT: garden_repository.get_light(),
            RedisKeys.LED_1: garden_repository.get_led_1_value(),
            RedisKeys.LED_2: garden_repository.get_led_2_value(),
            RedisKeys.LED_3: garden_repository.get_led_3_value(),
            RedisKeys.LED_4: garden_repository.get_led_4_value(),
            RedisKeys.IRRIGATOR_STATUS: garden_repository.get_irrigator_status().toString(),
            RedisKeys.IRRIGATION_SPEED: garden_repository.get_irrigation_speed()
        }),
        mimetype='application/json',
        status=200
    )


@app.route('/')
def serve_dashboard():
    return send_from_directory('garden-dashboard', 'index.html')


@app.route("/sse")
def stream():

    def eventStream():
        stream_pubsub = db.pubsub()
        stream_pubsub.subscribe("update-status")
        stream_pubsub.subscribe("update-controller")
        stream_pubsub.subscribe("update-sensorboard")

        while True:
            message = stream_pubsub.get_message()
            if message and message["type"] == "message":
                yield "data: {}\n\n".format(json.dumps(json.loads(message["data"].decode('utf-8'))))

    return Response(eventStream(), mimetype="text/event-stream")


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
