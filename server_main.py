import sys
from flask import Flask, Response
from flask_cors import CORS
import time

app = Flask(__name__)
CORS(app)

def generate():
	while(True):
		try:
			last_line = input()
		except:
			yield "DONE"
			print("DONE")
			return
		else:
			print(last_line + "\n")
			yield last_line + "\n"
			time.sleep(0.1)


@app.route('/')
def stream_response():
	return Response(generate())

if __name__ == "__main__":
	# generate()
	app.run()
