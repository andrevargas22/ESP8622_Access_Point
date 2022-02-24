# ESP8622 Access Point + Flask Client Example
This is a very simple code to run an ESP8266 as an access point to send and receive JSON data from clients, with a Flask code in Python to test it.

## Instructions

### Step 1 - Install ESP8266 boards on Arduino IDE:
- Open File > Preferences, and under Aditional Board Manager URLs, copy this: https://arduino.esp8266.com/stable/package_esp8266com_index.json
- Open Tools > Board > Board Manager, search for ESP8266 and install "esp8266" by "ESP8266 Community"

### Step 2 - Upload server.ino on the ESP8622:
- After installing the ESP8266 boards, they should be available under Tools > Board > ESP8266 Boards. I'm using board NodeMCU 1.0 (ESP-12E Module) because 
I have an ESP-12F in my possession, which is equivalent.

![alt text](https://github.com/andrevargas22/ESP8266_Access_Point/blob/main/images/img1.png)

- After that, just upload the code to the ESP. This video by Indrek Luuk has instructions on how to upload codes to different ESP boards using Arduino IDE: https://www.youtube.com/watch?v=_iX67plFeLs

### Step 3 - Get ESP IP address:
- After succesfully uploading the program, open the Serial Monitor and copy the Access Point IP address, which will be used to make client-side requests. There is an LED pin
declared in the server.ino code, which will keep blinking if no client is connected, and will be ON if a client is connected.

![alt text](https://github.com/andrevargas22/ESP8266_Access_Point/blob/main/images/img2.png)

This is it for the server. It is running and ready to accept requests. In the route '/json1', any connected client request a JSON from the ESP, and in the route '/json2', any connected client sends an JSON to the ESP.

## Flask-Client Test Example Python Code:
There are different ways to send requests. You could for example use Postman, just connect to the ESP Soft AP and send requests using the ESP IP address:

http:// + ESP_IP + /json1 -> Get Json
http:// + ESP_IP + /json2 -> Post Json

For this repo I created a small Flask server application that can be used to communicate with the ESP. To test it out, do the following steps:

### Step 1 - Install Requirements:
```
> pip install -r requirements.txt
```

### Step 2 - Paste ESP_IP on client.py:
- Update the ESP_IP variable with the same address copied from the ESP Serial Monitor

### Step 3 - Connect to the soft AP:
- The password is at server.ino

### Step 4 - Run flask code
On cmd:
```
> set FLASK_APP=client
> flask run
```
On PowerShell:
```
> $env:FLASK_APP="client.py"
> flask run
```

This should open a small page with instructions to both routes:

![alt text](https://github.com/andrevargas22/ESP8266_Access_Point/blob/main/images/img3.png)

Open /json1 to get a JSON from the ESP:

![alt text](https://github.com/andrevargas22/ESP8266_Access_Point/blob/main/images/img4.png)

Open /json2 to post a JSON to the ESP:

![alt text](https://github.com/andrevargas22/ESP8266_Access_Point/blob/main/images/img5.png)

Responses on the ESP8266:
![alt text](https://github.com/andrevargas22/ESP8266_Access_Point/blob/main/images/img6.png)





