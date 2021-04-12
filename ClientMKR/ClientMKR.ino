#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

#include "Secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SSID_WIFI;        // your network SSID (name)
char pass[] = PASSWORD_WIFI;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):

WiFiClient wifi;
HttpClient client = HttpClient(wifi, SERVER_URL, SERVER_PORT);
String endpoint = "";

void setup() {

  //Initialize serial and wait for port to open:

  Serial.begin(9600);
  Serial1.begin(4800); // Pin 13 e 14 del MKR

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  connettiWifi();
  
}

void loop() {
  //Serial1.println("ready...");
  while(Serial1.available()){
    Serial.println("Serial disponibile");
    endpoint = Serial1.readStringUntil('\n');
    int err = sendRequest("GET", endpoint);
    if(err==0){
      Serial.println("Richiesta HTTP effettuata con successo");
    }
    else{  
      Serial.println("Richiesta HTTP fallita");
    }
  }
  delay(500);
}

void checkResponse(){
  // if there are incoming bytes available
  // from the server, read them and print them:
  Serial.print("Attesa risposta...");
  while (!client.available()) {
    Serial.print(".");
  }
  Serial.println("");
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("status: ");
  Serial.println(statusCode);
  Serial.println(response);
  Serial1.println(endpoint);
  delay(100);
  Serial1.println(response);
  delay(500);
}

int sendRequest(String method, String endpointUrl){
  Serial.println("Inizio request");
  endpointUrl.trim();
  
  int str_len = endpointUrl.length() + 1; 
  char endpointChar[str_len];
  endpointUrl.toCharArray(endpointChar, str_len);

  Serial.print(endpointChar);
  Serial.println("---");
  int err = client.get(endpointChar);
  checkResponse();
  Serial.println("fine request");
  return err;
}

void connettiWifi(){
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
