while true; do
	./ogn-decode | python es/ogn_decode_parser.py
	sleep 10
done
