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
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED) {/*when we have wifi connection*/
        delay(1000);
        //Serial.print("Still trying to connect");
    }
    //Serial.print("Connected");
}

void loop() {
  bool done = false;

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
          done = true;
          //Serial.println(data);
      }

    if (done) /*If there is a valid input sent the ESP-01 board*/
    {
      //Make sure that data is null terminated
      //data[len] = '\0';

      // Create postData only at this point 
      String postData = "{\"Node_ID\":1994,\"data\":\""+ data + "\"}";
      // The following code will send a post request to the server.
      // I had to use a new string for the host name as the char array was
      // behaving in different than I had anticapted (string_host)
      http.begin("http://" +string_host + API_path);
      http.addHeader("Content-Type", "application/json");
      http.POST(postData);
      http.end();

      //Reset variables
      len = 0;
      data = "";
      done = false;
    }
  }
}
