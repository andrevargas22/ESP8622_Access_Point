#
#   @ File: client.py
#   
#   @ Author: André Vargas (https://github.com/andrevargas22)
#
#   @ This code is a small client example to interact with my ESP8266 Soft Access Point code to send and recieve json data
#

# Imports
import requests
from flask import Flask, request
from requests.auth import HTTPBasicAuth

app = Flask(__name__)

# This IP address must be the same IP given by the ESP at the start of server.ino code, run it once, open the terminal and copy paste the IP here
ESP_IP = '192.168.4.1'

# Authenticator
account = 'admin'
password = 'esp12f'

# Main Page
@app.route("/")
def hello_world():
    return "<p>Routes: </p> <p> /json1 : Receive json from ESP </p> <p> /json2 : Post json to ESP </p>"

# Recieve Json from ESP
@app.route('/json1', methods=['GET', 'POST'])
def getJsonHandler():
    content = requests.get('http://' + ESP_IP + '/json1', auth=HTTPBasicAuth(account, password), timeout = 0.5)    
    return content.json()

# Post Json to ESP
@app.route('/json2', methods=['GET', 'POST'])
def postJsonHandler():
    
    # This is a random json with the same keys defined on the ESP code
    random_json = { 'Var1': 100,
                    'Var2': 2301,
                    'Var3': 12,
                    'Var4': 0,
                    'Var5': 43
                    }

    p = requests.put('http://' + ESP_IP + '/json2', json= random_json, auth=HTTPBasicAuth(account, password))   
    return 'Json posted'

