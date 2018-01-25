#!/bin/sh
#
# kjolley
# squalor heights, ca, usa
# !date
#
me=$( basename "${0}" )

deviceid='00800001eb'
apikey='ebac74ce-987f-4411-8f43-87f876e14d9a'

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
