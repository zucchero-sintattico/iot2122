from flask import Flask
import redis

db = redis.Redis("redis")

db.set("counter", 0)

app = Flask(__name__)

@app.route('/')
def index():
    return "conteggio: " + str(int(db.get("counter")))

@app.route('/incr')
def incrementa():
    db.incr('counter')
    return 'incrementato'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)