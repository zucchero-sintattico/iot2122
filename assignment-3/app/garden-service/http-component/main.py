import redis, json
from flask import Flask
from flask import request
from flask import Response

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

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)