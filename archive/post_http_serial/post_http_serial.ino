// Include the Espressif NONOS SDK library
extern "C" {
    #include "user_interface.h"
}

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

WiFiServer server(2000);
WiFiClient client; /*socket*/

const char *ssid = "Room006";
const char *password = "ohDofa5rei9iSh4c";
const char *host="sbsrv1.cs.nuim.ie";
const int Port=80;
String string_host="sbsrv1.cs.nuim.ie";
String API_path="/fyp/ogrady/php/Record.php";
String PostData;
HTTPClient http;
bool connected=false;

void setup() {
    Serial.begin(9600);
    delay(10);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED) {/*when we have wifi connection*/
        delay(10);
    }
    delay(10);
}

void loop() {
  int i = 0;
//use the soket client for the TCP connection

  if(!connected)
  {
    PostData = "{\"Node_ID\":1994,\"data\":\"";
    if(Serial.available()){
      while(Serial.available()){
        PostData = PostData + char(Serial.read());
        i++;
        }
      }
     PostData = PostData + "\"}";
    if ((PostData.charAt(PostData.length()-3) == '\r')) /*If there is a valid input sent the ESP-01 board*/
    {
      // The following code will send a post request to the server.
      // I had to use a new string for the host name as the char array was
      // behaving in different than I had anticapted (string_host)
      http.begin("http://" +string_host + API_path);
      http.addHeader("Content-Type", "application/json");
      http.POST(PostData);
      http.end();
    }
  }
     delay(100);
}
