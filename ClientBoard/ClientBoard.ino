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
    }

    if(receivedString=="now") { httpGetPrenotazioneAttuale(); }
    if(receivedString=="next") { httpGetPrenotazioneSuccessiva(); }
    if(receivedString=="count") { httpPostCounter(); }
    if(receivedString=="temp") { httpPostTemperature(); }
}

void httpGetPrenotazioneAttuale(){
    // TODO Chimata http a /findPrenotazioneAttuale
    Serial1.print("Json ricevuto da http");
}
void httpGetPrenotazioneSuccessiva(){
    // TODO Chimata http a /findPrenotazioneSuccessiva 
    Serial1.print("Json ricevuto da http");
}
void httpPostCounter(){
    while(Serial1.available()){
        int counter = Serial1.read();
        // TODO Chimata http a /counter con variabile counter nel body
    }
}
void httpPostTemperature(){
    while(Serial1.available()){
        int temperature = Serial1.read();
        // TODO Chimata http a /temperaqturaStanza  con la temperatura nel body
    }
} 