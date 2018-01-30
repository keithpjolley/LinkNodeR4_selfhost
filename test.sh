#!/bin/sh
#
# kjolley
# squalor heights, ca, usa
# !date
#
me=$( basename "${0}" )

deviceid='00800001eb'
apikey='__devicekey__'

# register
register='{"action":"register","deviceid":"'"${deviceid}"'","apikey":"'"${apikey}"'"}'

# query
query='{"action":"query","deviceid":"'"${deviceid}"'","apikey":"'"${apikey}"'","params": ["R4"]}'

h1='Content-Type: application/json'
host='www.linksprite.io'
path='/api/http'
url="http://${host}${path}"

#echo curl -i -H "${h1}" -d "${query}" -XPOST "${url}"
curl -i -H "${h1}" -d "${register}" -XPOST "${url}"
#curl -i -H "${h1}" -d "${query}" -XPOST "${url}"
echo ''
