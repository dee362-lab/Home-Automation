from flask import Flask, request, jsonify

app = Flask(__name__)

# Store received data
sensor_data = {}

@app.route('/data', methods=['POST'])
def receive_data():
    global sensor_data
    sensor_data = request.json  # Receive JSON data from ESP32
    print("Received Data:", sensor_data)
    return jsonify({"message": "Data received successfully"}), 200

@app.route('/data', methods=['GET'])
def send_data():
    return jsonify(sensor_data)  # Send latest sensor data to the mobile app

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)