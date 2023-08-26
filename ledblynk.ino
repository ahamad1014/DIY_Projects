//Tech Trends Shameer
//Control LED Using Blynk 2.0/Blynk IOT

#define BLYNK_TEMPLATE_ID "TMPL3vV2qJv9c"
#define BLYNK_TEMPLATE_NAME "LED Control"
#define BLYNK_AUTH_TOKEN "WMXhElSKNPbdpEyqYp0JFHHcMs8FagBC"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
// WiFi Credentials
const char* ssid = "Enter your WIFI Name";
const char* password = "Enter Your WIFI password";

int ledpin = D2;
void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);    
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  Blynk.run(); 
}
