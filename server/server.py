from flask import Flask, request, jsonify
import json

app = Flask(__name__)

@app.route('/update', methods=['GET'])
def receive_data():
    data = request.args  
    print(data)  
    with open('data.txt', 'a') as file:
        file.write(json.dumps(data) + '\n')
    return jsonify({"message": "Data received", "data": data}), 200 

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)