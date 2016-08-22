import re
import sys
import datetime
from elasticsearch import Elasticsearch
import json
import argparse

# Requires elasticsearch python package
# > pip install elasticsearch
# Probably also requires some other stuff like perl

# Global configuration:
# Elastic type name, mostly don't care so naming it loc
elastic_type = "loc"


def main():
	global es, args

	parser = argparse.ArgumentParser(description="Parse OGN decode stream and upload to ES")
	parser.add_argument("--dry-run", action="store_true", help="Do not upload")
	parser.add_argument("--input-file", help="Read OGN decode data from file instead of stdin")
	parser.add_argument("--no-pass-through", help="Do not print out the decode stream during decoding", action="store_true")
	parser.add_argument("--es-server", help="URL:port to elasticsearch", default="localhost:9200")
	args = parser.parse_args()

	
	# Setup
	es = Elasticsearch([args.es_server])


	# Attempt to write a typemapping first
	typemapping = json.dumps({
		"mappings" : {
			elastic_type : {
				"properties" : {
					"position" : {"type":"geo_point"}
				}
			}
		}})


	#print typemapping
	es.indices.create(index="enop_flarm", body=typemapping, ignore=400)

	#
	# Keep this alive and waiting for lines
	if args.input_file:
		file = open(args.input_file, "r")
		for line in file:
			parseline(line)
		file.close()
	else: 
		while True:
			line = sys.stdin.readline()
			parseline(line)
	exit(0)

def parseline(line):
	global es, args

	fieldsre = re.search("([0-9.]+)MHz:[ ]+[0-9]:[0-9]:([^ ]+)[ ]+[0-9]+:[ ]+(\[.*\])deg[ ]+([0-9]+)m[ ]+([-+]?[0-9.]+)m\/s[ ]+([0-9.]+)m\/s[ ]+([0-9.]+)deg[ ]+([+-]?[0-9.]+)deg\/sec[ ]+([0-9]+)[ ]+([0-9]+)x([0-9]+)m[ ]+([-+]?[0-9.]+)kHz[ ]+([(0-9.]+)dB[ ]+([0-9])e[ ]+([0-9.]+)km[ ]+([0-9.]+)deg[ ]+([-+]+[0-9.]+)deg", line)

	# Forward stdin
	if not args.no_pass_through:
		print line.rstrip()

	if not fieldsre: 
		return
	data = {}

	# 1 indexed	
	data["mhz"] = float(fieldsre.group(1))
	data["identifier"] = fieldsre.group(2)
	data["position"] = fieldsre.group(3).replace(" ","").replace("[","").replace("]","")
	data["altitude"] = float(fieldsre.group(4))
	data["vertical_speed"] = float(fieldsre.group(5))
	data["speed"] = float(fieldsre.group(6))
	data["heading"] = float(fieldsre.group(7))
	data["heading_change"] = float(fieldsre.group(8))
	data["signal_strength"] = float(fieldsre.group(13))
	data["distance"] = float(fieldsre.group(15))
	data["bearing"] = float(fieldsre.group(16))

	data["timestamp"] = datetime.datetime.now().isoformat()

	# Ship the data!
	if not args.dry_run:
		es.index(index="enop_flarm", doc_type="loc", body=json.dumps(data))

	print "** UPLOADED TO ES: **", data


main()


