 #ifdef ESP8266
 #include<ESP8266WiFi.h>
 #include<ESP8266mDNS.h>
 #elif defined(ESP32)
 #include<WiFi.h>
 #include<ESPmDNS.h>
 #else
 #error "Board not found"
 #endif.
 
 const int relay = 5;
 const int op = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);
  pinMode(op, OUTPUT);
}

void loop() {

  digitalWrite(relay, HIGH);
  delay(500);

  digitalWrite(relay, LOW);
  delay(500);
  // put your main code here, to run repeatedly:

}
