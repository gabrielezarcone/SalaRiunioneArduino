/*
    Questo codice deve essere inserito all'interno della board (ESP8266) che si occuperà di effettuare le chiamate HTTP al server.
    Riceve istruzioni dalla board principale (MEGA2560) attraversolo la comunicazione seriale.
*/

char receivedString[10];  

void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop(){
    if(Serial1.available()){
      receivedString = Serial.read();
      Serial.println(receivedString); 
    }
    delay(500);
}
