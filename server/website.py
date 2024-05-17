from flask import Flask, jsonify
import json

app = Flask(__name__)

@app.route('/data', methods=['GET'])
def get_data():
    data_list = []
    try:
        with open('data.txt', 'r') as file:
            for line in file:
                data_list.append(json.loads(line.strip()))
    except FileNotFoundError:
        return jsonify({"error": "Data file not found"}), 404

    return jsonify(data_list), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, debug=True)
