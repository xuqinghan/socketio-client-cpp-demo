from gevent import monkey
monkey.patch_all()
from flask_socketio import SocketIO
from flask_socketio import send, emit
from flask_cors import CORS

from flask import Flask, render_template, session, request, jsonify

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
app.config['JSON_AS_ASCII'] = False
CORS(app)
#socketio = SocketIO(app, async_mode="gevent", ping_timeout=10, cors_allowed_origins='*', cors_credentials=False)
socketio = SocketIO(app, ping_timeout=10, cors_allowed_origins='*', cors_credentials=False)

@app.route('/', methods=['GET'])
def handle_target_kind():
    return 'hello world'
    emit('m1')


#-------------socketio---------------------

@socketio.on('connect')
def handle_connect():
    print('connect')
    emit('from server', '哈哈哈')

@socketio.on('disconnect')
def handle_disconnect():
    print('Client disconnected', request.sid)


@socketio.on('message_empty')
def handle_message_empty():
    print('message_empty')

@socketio.on('message_str')
def handle_message_str(data):
    print('message_str ', data)

@socketio.on('message_two')
def message_two(d1, d2):
    print('message_two ', d1, d2)

# @sio.event
# def message_list(sid, data):
#     print('message_list ', data)

# @sio.event
# def message_list(sid, data):
#     print('message_list ', data)





if __name__ == '__main__':
    print('flask socketio start')
    socketio.run(app, host='0.0.0.0', port=5000)


