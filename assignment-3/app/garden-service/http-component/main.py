from time import sleep
import redis, json
from flask import Flask, request, Response, send_from_directory

db = redis.Redis("redis")
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

    return Response(
        json.dumps({
            "status": "error" if status is None else status.decode('utf-8'),
            "temperature": "error" if temperature is None else temperature.decode('utf-8'),
            "light": "error" if light is None else light.decode('utf-8')
            # other data
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
        pubsub.psubscribe("update-*")

        while True:
            message = pubsub.get_message()
            if message and message["type"] == "message":
                # TODO check sse format
                if message["channel"] == "update-status":
                    yield "data: {}\n\n".format(json.dumps({
                        "status": message["data"].decode('utf-8')
                    }))
                elif message["channel"] == "update-sensorboard":
                    yield "data: {}\n\n".format(json.dumps(message["data"].decode('utf-8')))
    
    return Response(eventStream(), mimetype="text/event-stream")

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)