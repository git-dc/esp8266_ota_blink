

/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com
  Arduino IDE example: Examples > Arduino OTA > BasicOTA.ino
*********/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Update these with values suitable for your network.

// cnk vars begin:
unsigned long currentTime;
const char* ssid = "2.4g";
const char* password = "dauyndauyn";
// cnk vars end;

// blink vars begin:
const int ESP_BUILTIN_LED = 2; // 2- blue, 0 - red
unsigned long thisLoop=millis();
unsigned long interval = 750;
bool ledState = HIGH;
bool blinking = true;
// blink vars end;

void setup_wifi() 
{
  delay(10);
  // wifi network cnk begin:
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // wifi network cnk end;
}

void setup() {
////////////////////////////////////////////////////////
//////////////// WIFI - OTA SETUP BEGIN ////////////////
////////////////////////////////////////////////////////
  
  Serial.begin(115200);
  Serial.println("Booting");

  setup_wifi(); // wifi cnk procedure;
  
  pinMode(ESP_BUILTIN_LED, OUTPUT);

  // ota setup begin:
  
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("esp8266_blink");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");
  
  
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  
  // ota setup end;

///////////////////////////////////////////////////////
////////////// WIFI - OTA SETUP COMPLETE //////////////
///////////////////////////////////////////////////////

}

void loop() {
  
  ArduinoOTA.handle();
  
  currentTime = millis();
  
  // blink blurb begin:
  if (blinking == true and (currentTime - thisLoop >= interval)){
    thisLoop=currentTime;
    if (ledState == LOW) { ledState = HIGH; } else ledState = LOW;
    digitalWrite(ESP_BUILTIN_LED, ledState);
  }  
  // blink blurb end;
  
}



