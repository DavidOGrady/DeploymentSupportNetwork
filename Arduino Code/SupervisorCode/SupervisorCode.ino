// Include the Espressif NONOS SDK library
extern "C" {
    #include "user_interface.h"
}

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

WiFiServer server(2000); // Wi-Fi Access Point object
HTTPClient http;         // HTTP Client object

// WiFiClient client; /*socket*/

const char *ssid = "<WiFi Name>";
const char *password = "<WiFi password>";
const char *host="<server host address>";
const int Port=80;
String API_path="<path to api directory>";
String Node_id = "<a unqiue Id to identify the node in the WSN>"; 

void setup() {
    Serial.begin(57600);
    //Serial.println("Serial->wifi->server demo bl 002");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED) {/*when we have wifi connection*/
        delay(1000);
    }
    //Serial.print("WiFi connected: ");
    //Serial.println(WiFi.status());
}

const String postPrefix = "{\"Node_ID\": 1994, \"data\": \"";
char buffer[80];
int len=0;

void loop() {

   if (Serial.available()) {
      while (Serial.available() && (len<79))
         buffer[len++] = char(Serial.read());
      buffer[len] = '\000';
   }

   if (len>0) {
      int status;
      //Serial.print("Read: ");
      //Serial.println(String(buffer));
      String postData = postPrefix + String(buffer) + "\"}";
      len = 0;
      http.begin("http://" +string_host + API_path);
      http.addHeader("Content-Type", "application/json");
      status = http.POST(postData);
      String payload = http.getString();
      http.end();
      //Serial.print("Posted: ");
      //Serial.println(postData);
      //Serial.print("Status: ");
      //Serial.println(status);
      //Serial.print("Response: ");
      //Serial.println(payload);
   }

   delay(1000);

}
