#!/usr/bin/env ruby

require 'open-uri'
require 'net/http'
require 'net/https'
require 'date'
require 'json'
require 'yaml'

require_relative './passwords.rb'

UPLOAD_FREQUENCY = 60
ALTITUDE = 1834

def hpa_to_inches(hpa)
	return hpa * 0.02953
end

def celsius_to_fahrenheit(c)
	return (c * (9/5.0) + 32)
end

def qfe_to_qnh(qfe)
	return qfe + (ALTITUDE / 12.0) * 0.44
end

def calc_dewpoint(temp, humidity)
	return (humidity ** (1/8.0))* (112 + 0.9*temp) + 0.1*temp - 112.0
end

def save_for_wps(qfe, temperature, humidity)
	dewpoint = calc_dewpoint(temperature, humidity)
	params = { 
		:time => Time.now.iso8601(),
		:baromin => hpa_to_inches(qfe_to_qnh(qfe)),
		:tempf => celsius_to_fahrenheit(temperature),
		:dewptf => celsius_to_fahrenheit(dewpoint),
		:humidity => (humidity*100).to_i
		}
	p params	
	File.open("/tmp/meteo.yaml", "w") do |f|
		f.write params.to_yaml
		p f
	end
	p params
end

def upload_es(qfe, temperature, humidity)
	index = Date.today.strftime("readings_%Y-%m")
	uri = URI.parse("https://b678ca11873d9c89aa920060051e30b1-eu-west-1.foundcluster.com:9243/#{index}/meteo")
	params = { 
		:@timestamp => Time.now.iso8601(),
		:temp => temperature,
		:qfe => qfe,
		:qnh => qfe_to_qnh(qfe),
		:humidity => humidity,
		:dewpoint => calc_dewpoint(temperature, humidity),
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
		p res
	rescue Exception => e
		puts "es upload failed: #{e.message}"
		puts e.backtrace
	end
end

def get_value(type)
	data = `./Binaries/linux/armhf/Y#{type} all get_currentValue`
	if data =~ /OK: .* = (-?[0-9\.]+)\./
		return $1.to_f
	end
	raise "failed to prase #{data}"
end

while true
	begin
		qfe = get_value("Pressure")
		temp = get_value("Temperature")
		humidity = get_value("Humidity") / 100.0
		save_for_wps(qfe, temp, humidity)
		upload_es(qfe, temp, humidity)
	
	rescue Exception => e
		puts "woops: #{e.message}"
	end
	sleep 60
end
