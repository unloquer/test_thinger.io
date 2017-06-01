#define _DISABLE_TLS_
#define _DEBUG_
#define THINGER_SERVER "174.138.53.126"
#define USERNAME "uagaviria"
#define DEVICE_ID "espbrolin"
#define DEVICE_CREDENTIAL "j#1#A%HWbbUx"

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(2, OUTPUT);

  Serial.begin(115200);
  thing.add_wifi("C3P", "trespatios");

  // resource input example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << [](pson& in){ digitalWrite(2, in ? HIGH : LOW); };

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> [](pson& out){ out = millis(); };

  // resource input/output example (i.e. passing input values and do some calculations)
  thing["in_out"] = [](pson& in, pson& out){
    out["sum"] = (long)in["value1"] + (long)in["value2"];
    out["mult"] = (long)in["value1"] * (long)in["value2"];
  };
}

void loop() {
  thing.handle();
}
