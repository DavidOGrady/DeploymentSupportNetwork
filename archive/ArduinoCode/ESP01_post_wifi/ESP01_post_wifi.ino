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
String string_host="sbsrv1.cs.nuim.ie";
String API_path="/fyp/ogrady/php/Record.php";
String PostData = "{\"Node_ID\":1994,\"data\":\"Hello. I can send this thanks to the wifi library.\" }";
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

void loop() {

//use the soket client for the TCP connection

  if(!connected)
  {
    Serial.print("connecting to ");
    Serial.println(host);
    if (client.connect(host,Port)) /*If the client is connected to the server*/
    {
      Serial.println("connected");
      Serial.println("[Sending a request]");
      Serial.println(PostData);
      // The following code will send a post request to the server.
      // I had to use a new string for the host name as the char array was
      // behaving in different than I had anticapted (string_host)
      client.println("POST "+ API_path +" HTTP/1.1");
      client.println("Host: " + string_host);
      client.println("Cache-Control: no-cache");
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(PostData.length());
      client.println();
      client.println(PostData);
      connected = true;
    }else {
      Serial.println("connection failed");
    }
  }

// client.print("Hello\n");/*send data to server*/
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
