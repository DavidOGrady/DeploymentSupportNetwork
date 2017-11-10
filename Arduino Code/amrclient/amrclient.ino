// Include the Espressif NONOS SDK library
extern "C" {
    #include "user_interface.h"
}

#include <ESP8266WiFi.h>

WiFiServer server(2000);
WiFiClient client; /*socket*/

const char *ssid = "Room006";
const char *password = "ohDofa5rei9iSh4c";
const char *host="sbsrv1.cs.nuim.ie";
const int Port=80;
bool connected=false;

void setup() {

    Serial.begin(115200);
    delay(10);
 // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");


    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED) {/*when we have wifi connexion*/
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);

    


}
String API_path="/fyp/ogrady/";

void loop() {
  
//use the soket client for the TCP connection
  
  if(!connected)
  {
    Serial.print("connecting to ");
    Serial.println(host);
    if (client.connect(host,Port)) /*If the client is connected to the server*/
    
  {
      Serial.println("connected");
      client.println(".");
      connected = true;
    }
    
    else {
      Serial.println("connection failed");
    }  
  }

client.print("Hello\n");/*send data to server*/
delay(1000);

  bool dataStillAvailable = true;
  while(dataStillAvailable){
    if (client.available()) { /*If the data is available*/
         
      unsigned char l= client.read();/*recieve from the server*/
      Serial.printf("%c",l);
     
    }
    else{
      dataStillAvailable = false;    
    }
  }
  
    delay(1000);
      
}









