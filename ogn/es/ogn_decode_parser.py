import re
import sys
import os
import datetime
import urllib3
from elasticsearch import Elasticsearch
import json
import argparse

# Requires elasticsearch python package
# > pip install elasticsearch

# Global configuration:
elastic_type = "loc"
elastic_index = "enop_flarm"


def main():
	global ess, args

	parser = argparse.ArgumentParser(description="Parse OGN decode stream and upload to ES")
	parser.add_argument("--dry-run", action="store_true", help="Do not upload")
	parser.add_argument("--input-file", help="Read OGN decode data from file instead of stdin. Note that this will timestamp all entries with current time.")
	parser.add_argument("--no-pass-through", help="Do not print out the input stream during decoding", action="store_true")
	args = parser.parse_args()

	# Supports one or multiple configurations
	with open(os.path.dirname(__file__)+"/configuration.json") as file:
		configuration = json.load(file)
		configuration = [configuration] if isinstance(configuration, dict) else configuration

	# Disable warnings of missing SSL certs in urllib3
	# If you want this checking, it should go through the elasticsearch lib and verify_certs
	urllib3.disable_warnings()

	# Elasticsearch instances
	ess = []
	for config in configuration:
		instance = Elasticsearch(
			[config["host"]],
			http_auth=(config["username"], config["password"]),
			port=config["port"],
			use_ssl=config["use_ssl"],
			verify_certs=False #TODO: Reenable when you have working root certs
		)
		ess.append(instance)

	
	# Attempt to write a typemapping first
	typemapping = {
		"template" : "enop_flarm*",
		"mappings" : {
			elastic_type : {
				"properties" : {
					"position" : {"type":"geo_point"}
				}
			}
		}
	}


	# For timestamped index add a template:
	for es in ess:
		# TODO: This should be reenabled, but sometimes you do not have template rights...
		#es.indices.put_template(name="enop_template", body=json.dumps(typemapping))

		# Optionally just create one index
		#es.indices.create(index="enop_flarm", body=json.dumps(typemapping))
		pass

	try:
		# Keep this alive and waiting for lines
		if args.input_file:
			file = open(args.input_file, "r")
			for line in file:
				parseline(line)
			file.close()
		else: 
			# For stdin, had to write a custom reader...
			buff = ''
			while True:
				buff += sys.stdin.read(1)
				if buff.endswith('\n'):
					parseline(buff)
					buff = ''
	except KeyboardInterrupt:
		sys.stdout.flush()
		pass

def parseline(line):
	global ess, args

	fieldsre = re.search("([0-9.]+)MHz:[ ]+([^ ]+)[ ]+[0-9]+:[ ]+(\[.*\])deg[ ]+([0-9]+)m[ ]+([-+]?[0-9.]+)m\/s[ ]+([0-9.]+)m\/s[ ]+([0-9.]+)deg[ ]+([+-]?[0-9.]+)deg\/s[ ]+([_0-9]+)[ ]+([0-9]+)x([0-9]+)m[ ]+([0-9a-zA-Z_]+)[ ]+([:0-9a-zA-Z_]+)[ ]+([-+]?[0-9.]+)kHz[ ]+([(0-9.]+)\/([(0-9.]+)dB\/([0-9]+)[ ]+([0-9])e[ ]+([0-9.]+)km[ ]+([0-9.]+)deg[ ]+([-+]+[0-9.]+)deg", line)

	# Forward stdin
	if not args.no_pass_through:
		print(line.rstrip())

	if not fieldsre:
		# We skip upload of very common lines with little value
		if re.match("(APRS ->)|(APRS time)", line):
			print("** Skipping upload of common APRS line **")
			return

		# All other lines we upload (cpu info etc)
		data = {}
		data["line"] = line

		rightnow = datetime.datetime.now()
		data["timestamp"] = rightnow.isoformat()

		for es in ess:
			es.index(index="enop_rawlog", doc_type="lines", body=json.dumps(data))

		print("** Uploaded raw log line to ES **")

		# But you should always return here
		return

	try:
		data = {}

		# 1 indexed	
		data["mhz"] = float(fieldsre.group(1))
		data["identifier"] = fieldsre.group(2).split(":")[-1]
		data["position"] = fieldsre.group(3).replace(" ","").replace("[","").replace("]","")
		data["altitude"] = float(fieldsre.group(4))
		data["vertical_speed"] = float(fieldsre.group(5))
		data["speed"] = float(fieldsre.group(6))
		data["heading"] = float(fieldsre.group(7))
		data["heading_change"] = float(fieldsre.group(8))
		data["signal_strength0"] = float(fieldsre.group(15))
		data["signal_strength1"] = float(fieldsre.group(16))
		data["distance"] = float(fieldsre.group(19))
		data["bearing"] = float(fieldsre.group(20))
		data["bearing_change"] = float(fieldsre.group(21))

		rightnow = datetime.datetime.now()
		data["timestamp"] = rightnow.isoformat()

		# Month based indexing:
		#timeindex = "enop_flarm-"+str(rightnow.year)+"-"+str(rightnow.month)
		# Week based indexing:
		(year,week, dontcare) = rightnow.isocalendar()
		timeindex = "enop_flarm-"+str(year)+"-w"+str(week)

		# Ship the data!
		if not args.dry_run:
			for es in ess:
				es.index(index=timeindex, doc_type=elastic_type, body=json.dumps(data))

		print("** Position data detected, uploading to ES: **", data)

	except:
		print("** Something went wrong with ogn_decode_parser: ",sys.exc_info())


main()


