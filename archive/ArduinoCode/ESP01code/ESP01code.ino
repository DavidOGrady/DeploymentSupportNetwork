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
String data = "";
int len = 0; 
HTTPClient http;
bool connected=false;

void setup() {
    Serial.begin(57600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED) {/*when we have wifi connection*/
        delay(10);
    }
}

void loop() {

  if(!connected)
  {
    if(Serial.available() > 0){
        
        char ch; 
        do{
          ch = char(Serial.read());
          if(len<126){
            data = data + ch;
            len++;
            delay(10); // Adding this delay seems to stop the text from being sent in scraps
            }
          }while((ch!='\r')&&(len < 126));
          Serial.println(data);
          Serial.println(len);
      }

    if ((len>0) && (data.charAt(len-1)=='\r')) /*If there is a valid input sent the ESP-01 board*/
    {
      // Create postData only at this point 
      String dataString = String(data);
      String postData = "{\"Node_ID\":1994,\"data\":\""+ dataString + "\"}";
      http.begin("http://" +string_host + API_path);
      http.addHeader("Content-Type", "application/json");
      http.POST(postData);
      http.end();

      //Reset variables
      len = 0;
      data = "";
    }
  }
}
