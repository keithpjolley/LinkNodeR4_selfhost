# LinkNodeR4_selfhost
LinkNode R4 ESP8266 code to POST and receive JSON data

## tl;dr
This is an Arduino .ino file that POSTS data and parses
the response. This response is used to set the state of
the relays.

The associated "server" software is
[here](https://github.com/keithpjolley/LinkNodeR4_selfhost).

## our story
The purpose of this is to get a Linknode R4 to send/receive json
data to a web server. I tried to get the sample code/API working
without any luck and after much googling came to the conclusion
that nobody else had had any luck either. I was able to get the
iPhone app to talk to the linksprite.io server but I couldn't get
any succesfull communication from the device to/from the webserver.
Writing my own scripts to test linksprite.io against the published
API didn't work so I created my own.

There are two parts to this code. This is the "client" and I'll
link to the server here as soon as I upload it. (*done - ed*)
I didn't bother adding any security into it because at this point
I'm not planning on running it outside of my home LAN. If I change
that I'll update the code but for now the plan would be for my
home computer to act as a gateway to any external services.

To get this working I added the following url to the "Additional
Boards Manager" in Arduino Preferences:<br>
http://arduino.esp8266.com/stable/package_esp8266

To program the R4 I used this FTDI USB cable:<br>
https://www.adafruit.com/product/70

The device is a LinkNode R4 Version 1.0 06/01/2016
http://www.linksprite.com
