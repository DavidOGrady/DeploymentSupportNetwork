// Include the Espressif NONOS SDK library
extern "C" {
    #include "user_interface.h"
}

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

WiFiServer server(2000); // Wi-Fi Access Point object
HTTPClient http;         // HTTP Client object

// WiFiClient client; /*socket*/

const char *ssid = "Room006";
const char *password = "ohDofa5rei9iSh4c";
const char *host="sbsrv1.cs.nuim.ie";
const int Port=80;
String string_host="sbsrv1.cs.nuim.ie";
String API_path="/fyp/ogrady/api/Record.php";

void setup() {
    Serial.begin(9600);
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

   if (len>0) { //Potential bug here
    int x = 0;
    while(x<len+1){
        int status;
        //Serial.print("Read: ");
        //Serial.println(String(buffer));
        String postData = postPrefix + String(buffer[x]) + "\"}";
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
        ++x;
    }
    len = 0;
   }

   delay(1000);

}
