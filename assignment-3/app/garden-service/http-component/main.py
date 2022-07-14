from time import sleep
import redis, json
from flask import Flask, request, Response, send_from_directory
from lib.garden_repository import GardenRepository, Status

db = redis.Redis("redis")
app = Flask(__name__)
garden_repository = GardenRepository(db)

@app.route('/status', methods = ['GET'])
def get_status():
    return json.dumps({'status': garden_repository.get_status()}) + "\n"

@app.route('/status', methods = ['POST'])
def post_status():
    status = request.get_data().decode('utf-8')
    if status == Status.AUTO or status == Status.MANUAL:
        garden_repository.set_status(status)
        db.publish('update-status', json.dumps({'status': status}))
        return Response("Status changed\n", mimetype='text/plain', status=200)
    else:
        return Response("Error on status\n", mimetype='text/plain', status=400)

@app.route('/garden-dashboard/<path:path>')
def get_dashboard_files(path):
    return send_from_directory('garden-dashboard', path)

@app.route('/dashboard-status', methods = ['GET'])
def get_dashboard_status():

    return Response(
        json.dumps({
            "status": garden_repository.get_status(),
            "temperature": garden_repository.get_temperature(),
            "light": garden_repository.get_light(),
            "led1": garden_repository.get_led_1_value(),
            "led2": garden_repository.get_led_2_value(),
            "led3": garden_repository.get_led_3_value(),
            "led4": garden_repository.get_led_4_value(),
            "irrigator_status": garden_repository.get_irrigator_status(),
            "irrigation_speed": garden_repository.get_irrigation_speed()
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
        pubsub = db.pubsub()
        pubsub.subscribe("update-status")
        pubsub.subscribe("update-controllerStatus")
        pubsub.subscribe("update-sensorboard")

        while True:
            message = pubsub.get_message()
            if message and message["type"] == "message":
                yield "data: {}\n\n".format(json.dumps(json.loads(message["data"].decode('utf-8'))))
    
    return Response(eventStream(), mimetype="text/event-stream")

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)