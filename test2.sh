#!/bin/sh
#
# kjolley
# squalor heights, ca, usa
# !date
#
me=$( basename "${0}" )
tmp="/tmp/${me}.$$"

__KJ__LOCAL__="true"

if [ "${__KJ__LOCAL__}" == "true" ]
then
  host='localhost'
  post='POST /linknode HTTP/1.1'
else
  host='www.linksprite.io'
  post='POST /api/http HTTP/1.1'
fi

deviceid='00800001eb'
devkey='__devicekey__'
userkey='__userkey__'

dev='"deviceid":"'"${deviceid}"'","apikey":"'"${devkey}"'",'
user='"deviceid":"'"${deviceid}"'","apikey":"'"${userkey}"'",'

#register='{'"${dev}"'"action":"register"}'
update='{'"${dev}"'"action":"update","params":{ "bar": [ "alpha", "beta", "gamma", "foo" ], "relays": "0000" }}'
query='{'"${dev}"'"action":"query"}'

action="${query}"
if [ -n "${1}" -a "${1}" = "update" ]; then
  action="${update}"
elif [ -n "${1}" -a "${1}" = "query" ]; then
  action="${query}"
fi

length="$(echo "${action}" | tr -d '\n' | wc -c | tr -d ' ')"
port='80'

echo "${me}: Sending: ---"
cat<<EOF | tee "${tmp}"
${post}
Host: ${host}
Content-Type: application/json
Content-Length: ${length}

${action}




EOF
echo "---"

/usr/bin/nc "${host}" "${port}" < "${tmp}"
echo ''
rm "${tmp}"
