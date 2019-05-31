#!/usr/bin/env ruby

require 'open-uri'
require 'net/http'
require 'net/https'
require 'date'
require 'json'
require 'yaml'

require_relative './passwords.rb'

WIND_READINGS = []

UPLOAD_FREQUENCY = 10

def upload_windy(avgdir, avgmps, gustmps)
	uri = URI("https://stations.windy.com/pws/update/#{WINDYKEY}")

	params = {
		:winddir => avgdir,
		:wind => avgmps,
		:gust => gustmps
		}

	begin
		slow_params = YAML.load_file('/tmp/meteo.yaml')
		time_diff = Time.now - Time.parse(slow_params[:time])
		if time_diff > 300
			raise "more than 300s since last meteo update in /tmp/meteo.yaml"
		end
		params[:tempf] = slow_params[:tempf]
		params[:humidity] = slow_params[:humidity]
		params[:baromin] = slow_params[:baromin]
	rescue Exception => e
		puts("slow params fail: #{e}")
	end

	uri.query = URI.encode_www_form(params)

	begin
		res = Net::HTTP.get_response(uri)
		puts res.body if res.is_a?(Net::HTTPSuccess)
	rescue Exception => e
		puts "windy upload failed: #{e.message}"
	end
end

def upload_wps(avgdir, avgmps, gustdir, gustmps)
	uri = URI('http://rtupdate.wunderground.com/weatherstation/updateweatherstation.php')

	params = {
		:action => "updateraw", 
		:ID => "ISORTRON10",
		:PASSWORD => WUNDERPASS,
		:dateutc => Time.now.strftime("%Y-%m-%d %H:%M:%S"),
		:winddir => avgdir,
		:windspeedmph => avgmps * 2.24,
		:windgustdir => gustdir,
		:windgustmph => gustmps * 2.24,
		:realtime => 1,
		:rtfreq => UPLOAD_FREQUENCY
		}

	begin
		slow_params = YAML.load_file('/tmp/meteo.yaml')
		time_diff = Time.now - Time.parse(slow_params[:time])
		if time_diff > 300
			raise "more than 300s since last meteo update in /tmp/meteo.yaml"
		end
		slow_params.delete("time")
		params.merge!(slow_params)
	rescue Exception => e
		puts("slow params fail: #{e}")
	end

	uri.query = URI.encode_www_form(params)

	begin
		res = Net::HTTP.get_response(uri)
		puts res.body if res.is_a?(Net::HTTPSuccess)
	rescue Exception => e
		puts "wps upload failed: #{e.message}"
	end
end

def upload_es(avgdir, avgmps, gustdir, gustmps)
        index = Date.today.strftime("readings_%Y-%m")
	uri = URI.parse("https://b678ca11873d9c89aa920060051e30b1-eu-west-1.foundcluster.com:9243/#{index}/reading")
	params = { 
		:@timestamp => Time.now.iso8601(),
		:direction => avgdir,
		:wind => avgmps * 1.94,
		:gust => gustmps * 1.94,
		}

	begin
		http = Net::HTTP.new(uri.host, uri.port)
		http.use_ssl = true
		http.verify_mode = OpenSSL::SSL::VERIFY_NONE
		req = Net::HTTP::Post.new(uri.path)
		req.basic_auth("readwrite", ESPASS)
		req.body = params.to_json
		res = http.request(req)
		puts res.body if res.is_a?(Net::HTTPSuccess)
		p req.body
		p res
	rescue Exception => e
		puts "es upload failed: #{e.message}"
		puts e.backtrace
	end
end
# yeah, not quite (:
def average_direction(ary)
	return ary[0]	
end

def average_and_upload
	mpss = WIND_READINGS.map{ |e| e[:mps] }
	avgmps = (mpss.inject(:+) / mpss.size)
	avgdir = average_direction(WIND_READINGS.map { |e| e[:dir] })
	gust = WIND_READINGS.max_by{ |e| e[:mps] }
	upload_wps(avgdir, avgmps, gust[:dir], gust[:mps])
	upload_windy(avgdir, avgmps, gust[:mps])
	upload_es(avgdir, avgmps, gust[:dir], gust[:mps])
	WIND_READINGS.clear
end

def process(line)
	elements = line.split(',')
	raise ArgumentError unless elements[0] == "$IIMWV"
	raise ArgumentError unless elements.size == 6
	dir = elements[1].to_i
	mps = elements[3].to_f
	puts "read: #{mps} from #{dir}"
	WIND_READINGS << { :dir => dir, :mps => mps }
	if WIND_READINGS.size >= UPLOAD_FREQUENCY
		average_and_upload
	end
end

# Loop in case the FIFO dies
while true
	begin
		File.open("./wind", "r") { |fifo|
			while line = fifo.gets
				process(line)
				STDOUT.flush
			end
		}
	rescue ArgumentError
		STDERR.puts("bad data")
		sleep 5
	end
end
