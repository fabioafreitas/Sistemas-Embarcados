from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/')
def function():
        return "hello, world!"

@app.route('/post', methods=['POST'])
def function2():
        return jsonify({
		'int':0,
		'str':'foo'
	})


if __name__ == '__main__':
        app.run(host='0.0.0.0', port=80, debug=True)