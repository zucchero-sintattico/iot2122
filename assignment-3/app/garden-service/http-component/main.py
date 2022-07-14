from time import sleep
import redis, json
from flask import Flask, request, Response, send_from_directory

db = redis.Redis("localhost")
app = Flask(__name__)

@app.route('/status', methods = ['GET'])
def get_status():
    return json.dumps({'status': db.get('status').decode('utf-8')}) + "\n"

@app.route('/status', methods = ['POST'])
def post_status():
    status = request.get_data().decode('utf-8')
    if status == 'AUTO' or status == 'MANUAL':
        db.set('status', status)
        db.publish('update-status', status)
        return Response("Status changed\n", mimetype='text/plain', status=200)
    else:
        return Response("Error on status\n", mimetype='text/plain', status=400)

@app.route('/garden-dashboard/<path:path>')
def get_dashboard_files(path):
    return send_from_directory('garden-dashboard', path)

@app.route('/dashboard-status', methods = ['GET'])
def get_dashboard_status():
    status = db.get('status')
    temperature = db.get('temperature')
    light = db.get('light')
    led1 = db.get('l1')
    led2 = db.get('l1')
    led3 = db.get('l1')
    led4 = db.get('l1')
    irrigator = db.get('irrigator')
    irrigator_speed = db.get('irrigator_speed')

    return Response(
        json.dumps({
            "status": "error" if status is None else status.decode('utf-8'),
            "temperature": "error" if temperature is None else temperature.decode('utf-8'),
            "light": "error" if light is None else light.decode('utf-8'),
            "led1": "error" if led1 is None else led1.decode('utf-8'),
            "led2": "error" if led2 is None else led1.decode('utf-8'),
            "led3": "error" if led3 is None else led1.decode('utf-8'),
            "led4": "error" if led4 is None else led1.decode('utf-8'),
            "irrigator": "error" if irrigator is None else irrigator.decode('utf-8'),
            "irrigator_speed": "error" if irrigator_speed is None else irrigator_speed.decode('utf-8'),
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
                channel = message["channel"].decode('utf-8')
                
                if channel == "update-status":
                    status = message["data"].decode('utf-8')
                    yield "data: {}\n\n".format(json.dumps({
                        "status": status
                    }))
                elif channel == "update-sensorboard":
                    yield "data: {}\n\n".format(json.dumps(json.loads(message["data"].decode('utf-8'))))
                elif channel == "update-controllerStatus":
                    yield "data: {}\n\n".format(json.dumps(json.loads(message["data"].decode('utf-8'))))
    
    return Response(eventStream(), mimetype="text/event-stream")

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)