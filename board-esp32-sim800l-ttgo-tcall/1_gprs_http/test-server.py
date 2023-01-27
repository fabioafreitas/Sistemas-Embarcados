# run ngrok in a different console with this command, to expose the localhost api
# ngrok --scheme http http 8000

from flask import Flask, request, jsonify
from flask_cors import CORS
import requests as http

app = Flask(__name__)
cors = CORS(app, resources={r"/*": {"origins": "*"}})

@app.route('/', methods=['GET'])
def get():
        return jsonify({"http": "get"})

@app.route('/', methods=['POST'])
def post():
        return jsonify(request.get_json())

if __name__ == '__main__':
        app.run(host="127.0.0.1", port=8000)