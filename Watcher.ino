/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <EEPROM.h>

const char* ssid     = "BEZEQINT-6FF1";    //"uri";   "SHELEG";     //"erezphone";  //yaniv levy
const char* password = "4062920574";  //"12345678"; "111222777";  //"0317887630";       //"opel0";

const char* host = "www.alexshoyhit.com";  //"www.alexshoyhit.com"; "www.tankcare.shop";
const char* streamId   = "....................";
const char* privateKey = "....................";
String number="972523320940";
String message="hello world";
String url = "/";

String temperature="999";
String humid=      "444";
String weight=     "777";
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
float ii = 0;  //GetHum();
float xx = 0;  //GetTemp();
float zz = 0;  //GetTemp();

String t=  "3.25";
String h=  "4.25";
String w=  "5.25";
int I1 = 0;
int I2 = 0;
int I3 = 0;


void setup()
{
    Serial.begin(115200);
    Serial2.begin(9600);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

int value = 0;

void loop()
{
    //------------------------------------------------------------------------------
    readEpoch();
    //------------------------------------------------------------------------------
    delay(5000);
    ++value;

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    if (temperature.indexOf("WaterOK") >= 0)
    {
    //---------------------------------------------------------------------------------------
    // We now create a URI for the requestormal mode no Alarm (working)
    //
    url = "/";
 
    url += "?com=insert&temp="+ temperature +"&hu=" + humid+ "&we=" + weight;
    }
    //---------------------------------------------------------------------------------------
    else
    {
    url = "/sms.php";
     
    // We now create a URI for the request
    url += "?number="+ number +"&message=" + message;
    }
    //--------------------------------------------------------------------------------------- 

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
    temperature = "WaterOK";
    message = "WaterOK"; 
    delay(500);
}

//-------------------------------------------------------------------------------------------------
void readEpoch() {
  while (Serial2.available()) {

   //delay(10);  //small delay to allow input buffer to fill
   char inChar = Serial2.read();
    
   if(inChar != '>') 
   {
       // add it to the inputString:
       inputString += inChar; 
   }
   else 
   {
      stringComplete = true;
      
      Serial.println(inputString);     
      temperature = "WaterisOverflow"; 
      inputString = "";
      message = "Alarm"; 
   }
  }
}
