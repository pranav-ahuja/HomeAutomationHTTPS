
#ifdef ESP8266
#include<ESP8266WiFi.h>
#include<ESP8266mDNS.h>
#elif defined(ESP32)
#include<WiFi.h>
#include<ESPmDNS.h>
#else
#error "Board not found"
#endif

 const int relay = 5;
 const int op = 4;

//PROGMEM -> we are saving it in program memory
char webpage[] PROGMEM = R"====(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>LED Light control</title>

    <script type="text/javascript">

    </script>
  </head>
  <body style="background-color: aqua">
    <h1>My Home Automation</h1>

    <h3>LED 1</h3>
    <button onclick="window.location = 'http://'+ location.hostname +'/led1/on'">ON</button>
    <button onclick="window.location = 'http://'+ location.hostname +'/led1/off'">OFF</button>
  </body>
</html>

)===="; 
//string literal -> used to store html code

#include<ESPAsyncWebServer.h>

AsyncWebServer server(80);  //http protocol
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "test/plain", "Not Found");//sending it to the server (status code, method we are sending the data, payload)
}

void setup() {
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);
  pinMode(op, OUTPUT);
  Serial.begin(115200);
  WiFi.softAP("pranav", ""); //making esp board as a router so that mobile and laptop can be connected to it. Parameters include ("SSID", "Password")
  Serial.println("softAP");
  Serial.println(WiFi.softAPIP()); //Printing the IP provided by ESP

  //Starting a DNS Server
  if(MDNS.begin("esp")){//ESP/local
    Serial.println("MDNS started");
  }
  
  server.on("/", [](AsyncWebServerRequest *request) //Define home page of the web server
  {  
    request->send_P(200, "text/html", webpage); //sending it to the server (status code, method we are sending the data, payload); send_P -> we are reading it from program memory
  });
  
  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) //Define home page of the web server
  {
    digitalWrite(relay, HIGH);
    String message = "Light is on";
    request->send(200, "text/html", webpage); //sending it to the server (status code, method we are sending the data, payload)
  });

  server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest *request) //Define home page of the web server
  {
    digitalWrite(relay, LOW);
    String message = "Light is off";
    request->send(200, "text/html", webpage); //sending it to the server (status code, method we are sending the data, payload)
  });

  server.onNotFound(notFound);
  
  
  server.begin(); //start the webserver

}

void loop() {
  // put your main code here, to run repeatedly:

}
