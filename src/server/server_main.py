import sys
from flask import Flask, Response, render_template
import time
import json

app = Flask(__name__)


def clog_to_json(clog):
	clog = clog.split(":")

	if(clog[0] == "N"):
		# malloc / calloc node
		obj = dict()
		obj["sigtype"] = "SIGALOC"
		obj["alloctype"] = "node"

		if(clog[1] == "H"):
			obj["source_region"] = "heap"
			obj["source_addr"] = int(clog[2], 16)
			obj["source_index"] = int(clog[3])
			obj["dest"] =int(clog[4], 16)
		else:
			obj["source_region"] = "other"
			obj["source_addr"] = int(clog[2], 16)
			obj["dest"] = int(clog[3], 16)
		return obj

	if(clog[0] == "D"):
		obj = dict()
		obj["sigtype"] = "SIGALOC"
		obj["alloctype"] = "data"
		
		if(clog[1] == "H"):
			obj["source_region"] = "heap"
			obj["source_addr"] = int(clog[2], 16)
			obj["source_index"] = int(clog[3])
			obj["dest"] = int(clog[4], 16)
		else:
			obj["source_region"] = "other"
			obj["source_addr"] = int(clog[2], 16)
			obj["dest"] = int(clog[3], 16)
		return obj


	if(clog[0] == "F"):
		obj = dict()
		obj["sigtype"] = "SIGFREE"
		obj["addr"] = int(clog[1], 16)

		return obj

	if(clog[0] == "C"):
		obj = dict()
		obj["sigtype"] = "SIGCOPY"

		if(clog[1] == "H"):
			obj["source_region"] = "heap"
			obj["source_addr"] = int(clog[2], 16)
			obj["source_index"] = int(clog[3])
			obj["dest"] = int(clog[4], 16)
		else:
			obj["source_region"] = "other"
			obj["source_addr"] = int(clog[2], 16)
			obj["dest"] = int(clog[3], 16)
		return obj

	if(clog[0] == "B"):
		obj = dict()
		obj["sigtype"] = "SIGBRK"
		obj["label"] = clog[1]
		return obj
	else:
		return "{\"FAILURE\"}"


def generate():
	while(True):
		try:
			last_line = input()
		except:
			yield "\n"
			print("DONE")
			return
		else:
			print(last_line + "\n")
			yield json.dumps(clog_to_json(last_line)) + "\n"
			time.sleep(0.1)


@app.route('/stream')
def stream_response():
	return Response(generate())

@app.route('/')
def homepage():
	return render_template('index.html')

if __name__ == "__main__":
	# generate()
	app.run(port=5000)
