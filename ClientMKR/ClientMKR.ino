#include <SPI.h>
#include <WiFiNINA.h>

#include "Secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SSID_WIFI;        // your network SSID (name)
char pass[] = PASSWORD_WIFI;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):

WiFiClient client;

void setup() {

  //Initialize serial and wait for port to open:

  Serial.begin(9600);
  Serial1.begin(9600); // Pin 13 e 14 del MKR

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  // check for the WiFi module:

  if (WiFi.status() == WL_NO_MODULE) {

    Serial.println("Communication with WiFi module failed!");

    // don't continue

    while (true);

  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {

    Serial.println("Please upgrade the firmware");

  }

  // attempt to connect to Wifi network:

  while (status != WL_CONNECTED) {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:

    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection:
    delay(5000);

  }

  Serial.println("Connected to wifi");

  printWifiStatus();

  Serial.print("\nStarting connection to server...");
  Serial.println(SERVER_URL);
}

void loop() {
  //Serial.println("ready...");
  while(Serial.available()){
    String endpoint = Serial.readString();
    sendRequest("GET", endpoint);
  }
  checkResponse();
}

void checkResponse(){
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    Serial1.write(c);
  }
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    //Serial.println();
    //Serial.println("disconnecting from server.");
    client.stop();
  }
}

void sendRequest(String method, String endpoint){
  // if you get a connection, report back via serial:
  if (client.connect(SERVER_URL, SERVER_PORT)) {
    //Serial.println("connected to server: ");

    // Make a HTTP request:
    endpoint.trim();
    String request = method + " " + endpoint + " HTTP/1.1";
    client.println(request);
    client.print("Host: ");
    client.println(SERVER_URL);
    client.println("Connection: close");
    client.println();
  }
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your board's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
}
