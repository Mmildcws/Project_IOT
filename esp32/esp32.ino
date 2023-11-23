#include "EspMQTTClient.h"
#include "ArduinoJson.h"
#include <HardwareSerial.h>

unsigned long test = 0;

EspMQTTClient client(
  "AWIFI",
  "p1234wifi",
  "broker.hivemq.com",  // MQTT Broker server ip
  "",                   // Can be omitted if not needed
  "",                   // Can be omitted if not needed
  ""                    // Client name that uniquely identify your device
                        // The MQTT port, default to 1883. this line can be omitted
);

void setup() {
  Serial.begin(115200);                                                       // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater();                                              // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA();                                                         // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("start", "start");                             // You can activate the retain flag by setting the third parameter to true
}


void onConnectionEstablished() {
  client.subscribe("fibo/log", onMessageReceived);
}

void onMessageReceived(const String& topic, const String& message) {
  Serial.print(message);
}


void loop() {
  client.loop();
}