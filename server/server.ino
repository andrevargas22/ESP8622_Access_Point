/**
 *  @ File: server.ino
 *  
 *  @ Author: André Vargas (https://github.com/andrevargas22)
 *  
 *  @ This code runs a small Soft Access Point on a ESP8266 that is able to send and recieve 
 *  http requests, which can send and receive data from sensors to an application, for example.
 *  On this example there is an LED connected to pin 16 to show to user when a client is connected
 *  to the server.
 *  
*/

/***************
 * Libraries
****************/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

/***************
 * Setup
****************/
#define BAUD_RATE 115200

// Status LED
#define LEDR 16

// Define login and password for client requests
const char* CLIENT_LOGIN = "admin";
const char* CLIENT_PASSWORD = "esp12f";

// JSON files:
DynamicJsonDocument doc1(2048);
DynamicJsonDocument doc2(2048);

// JSON variables:
int var1, var2, var3, var4, var5;

// Web Server:
ESP8266WebServer server(80);

/*************
 * Functions
**************/
// Set the Access Point
void setSoftAP(){

  Serial.println("");
  Serial.println("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESPsoftAP_01", "pass-to-soft-AP");
  
  // Soft AP ready
  if(result == true){
      Serial.println("Ready");
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);
  }

  // Soft AP failed
  else{
      Serial.println("Failed!");
  }

  Serial.println("");

}

// Send Json with data after receiving a request
void sendJson() {

    // Server auth
    if (!server.authenticate(CLIENT_LOGIN, CLIENT_PASSWORD)) {
        String message1 = "Error 403 - Authentication Failed!";
        Serial.println(message1);
        server.send(403, "text/plain", message1);
        return;
    }
     
    Serial.println("*** JSON Requested ***");
    
    // Random JSON definition, you can change this up to your needs, using sensor readings for example
    doc1["Var1"] = 300;
    doc1["Var2"] = 12;
    doc1["Var3"] = 31;
    doc1["Var4"] = 15;
    doc1["Var5"] = 201;

    String json1 = "";

    // Serialize and send Json
    serializeJson(doc1, json1);
    Serial.print("Sent: ");
    Serial.println(json1);
    Serial.println("");
    server.send(200, "application/json", json1);
 
}

// Recieve Json from client
void receiveJson() {

    // Print received json
    Serial.println("*** JSON Received ***");
    String json2 = server.arg("plain");
    Serial.print("Received ->");
    Serial.println(json2);

    // Deserialize:
    deserializeJson(doc2, json2);
    var1 = doc2["Var1"];
    var2 = doc2["Var2"];
    var3 = doc2["Var3"];
    var4 = doc2["Var4"];
    var5 = doc2["Var5"];

    // Print all info received in separated variables:
    Serial.print("Variable 1: ");
    Serial.println(var1);

    Serial.print("Variable 2: ");
    Serial.println(var2);

    Serial.print("Variable 3: ");
    Serial.println(var3);

    Serial.print("Variable 4: ");
    Serial.println(var4);

    Serial.print("Variable 5: ");
    Serial.println(var5);
    Serial.println("");
    
    server.send(200);
    
}

// Handle not found requests
void handleNotFound() {
    Serial.println("Error 404 - Not Found");
    String message2 = "Error 404 - Not Found!";
    server.send(404, "text/plain", message2);
  
}

/*************
* Setup
*************/
void setup() {

    // Begin Serial
    Serial.begin(BAUD_RATE);

    // Status LED
    pinMode(LEDR, OUTPUT);
    digitalWrite(LEDR, HIGH);

    // Start Soft Access Point
    setSoftAP();

    // HTTP requests addresses
    server.on("/json1", sendJson);         
    server.on("/json2", receiveJson);
    server.onNotFound(handleNotFound);
  
    // Begin Server
    server.begin();
}

/*************
* Loop
*************/
void loop() { 

    // Checks constantly if there is a connection, and lights an LED if that is the case, otherwise keeps blinking
    if(WiFi.softAPgetStationNum() == 0){
      digitalWrite(LEDR, HIGH);
      delay(50);
      digitalWrite(LEDR, LOW);
      delay(50);
    }

    else{
      digitalWrite(LEDR, LOW);
    }

    // Wait for requests
    server.handleClient();
    
}   
