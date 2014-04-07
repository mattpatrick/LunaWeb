/*
  Repeating Wifi Web client
 
 This sketch connects to a a web server and makes a request
 using an Arduino Wifi shield.
 
 Circuit:
 * Wifi shield attached to pins 10, 11, 12, 13
 
 created 23 April 2012
 modifide 31 May 2012
 by Tom Igoe
 
 http://arduino.cc/en/Tutorial/WifiWebClientRepeating
 This code is in the public domain.
 */

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Shouldnt It Be Raven?";      //  your network SSID (name) 
char pass[] = "idrathernottellyou";   // your network password

int keyIndex = 0;            // your network key Index number (needed only for WEP)
const String key = "fevd4e5f9";
int status = WL_IDLE_STATUS;
int sensorState = 0;
int ledToggle = 2;
int analogThreshold = 1000; //The threshold value when the arduino will send a message

// Initialize the Wifi client library
WiFiClient client;

// server address:
IPAddress server(54,200,254,10);

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
boolean lastConnected = false;                  // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds

const int analogPin = A0; 

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

int buttonState = 0;   
int sentMessage = 1;

void setup() {
  
    Serial.begin(9600); 
  //********* HTTP SETUP ******************//
  
  //Initialize serial and wait for port to open:
//
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }
//  
//  // check for the presence of the shield:
//  if (WiFi.status() == WL_NO_SHIELD) {
//    Serial.println("WiFi shield not present"); 
//    // don't continue:
//    while(true);
//  } 
//  
//  // attempt to connect to Wifi network:
//  while ( status != WL_CONNECTED) { 
//    Serial.print("Attempting to connect to SSID: ");
//    Serial.println(ssid);
//    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
//    status = WiFi.begin(ssid, pass);
//
//    // wait 10 seconds for connection:
//    delay(10000);
//  } 
//  // you're connected now, so print out the status:
//  printWifiStatus();
//  
  //*********** OTHER SETUP *****************//
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);   
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  
  // ************* HTTP FUNCTION ****************//
//  while (client.available()) {
//    char c = client.read();
//    Serial.write(c);
//  }
//
//  // if there's no net connection, but there was one last time
//  // through the loop, then stop the client:
//  if (!client.connected() && lastConnected) {
//    Serial.println();
//    Serial.println("disconnecting.");
//    client.stop();
//  }
//
//  // if you're not connected, and ten seconds have passed since
//  // your last connection, then connect again and send data:
//  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
////    httpRequest();
//  }
//  // store the state of the connection for next time through
//  // the loop:
//  lastConnected = client.connected();
// 
//  
  int sensorVal = analogRead(A0);
//  Serial.println(sensorVal);
//  



  if ((analogRead(A0) > 310) && (sensorState == 0)) {     
    // turn LED on:    
    delay(500);
    
    //Digital debounce
    if (sensorVal > analogThreshold) {
//      Serial.println("Sending message..."); 
      sensorState = 1;
      Serial.println(sensorState);
//      httpRequest(true); 

    }
 
  } 
  
  if (analogRead(A0) <= analogThreshold && sensorState == 1) {
  
    delay(500);
    if (sensorVal <= analogThreshold) {
//        Serial.println("Setting sensorState low...");
        sensorState = 0;
        Serial.println(sensorState);
//        httpRequest(false); 
      }

}
}

// this method makes a HTTP connection to the server:
void httpRequest(boolean state) {
  
  String stateString = String(state);
  String keyString = "fevd4e5f9";
  
  Serial.println(stateString);
  Serial.println(keyString);
    String requestString = "POST /request";
    String httpString = " HTTP/1.1";
    requestString = requestString + "?bed=" + stateString + "&id=" + keyString + httpString; 
    Serial.println(requestString);
    // if there's a successful connection:
    if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:

    client.println(requestString);
    client.println("Host: 54.200.254.10");

    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void toggleLights() {
      digitalWrite(ledToggle, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(10);             // wait for a second
      digitalWrite(ledToggle, LOW);
}







