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
String API_path="/fyp/ogrady/api/Record.php";
char buffer[80];
int len=0;
HTTPClient http;

void setup() {
    // Listen to Serial Line @ baud rate of 57600
    Serial.begin(57600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED) {/*when we have wifi connection*/
        delay(10);
    }
}



void loop() {
    // While data is available on the Serial Line
    // read in the first 80 characters sent in from the node
    if(Serial.available() > 0){
      do{
        buffer[len] = char(Serial.read());
        }while(Serial.available()&&(len < 79));
        len++;
      buffer[len] = '\000';
    }

    if ((len>0) && (buffer[len-1]=='\r')) /*If there is a valid input sent the ESP-01 board*/
    {
      // Using a HTTP post request, Send data to server
      String dataString = String(buffer);
      String postData = "{\"Node_ID\":1994,\"data\":\""+ dataString + "\"}";
      http.begin("http://" +string_host + API_path);
      http.addHeader("Content-Type", "application/json");
      http.POST(postData);
      http.end();

      //Reset variables
      len = 0;
    }
}
