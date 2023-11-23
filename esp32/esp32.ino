
// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <Arduino_JSON.h>
// #include <HardwareSerial.h>

// const char* ssid = "Mmildcws";      //   Thakdanai_2.4GHz
// const char* password = "Mmildcws";  //   0917071901Ff
// const char* mqttServer = "broker.hivemq.com";
// const int mqttPort = 1883;

// unsigned long lastTime = 0;
// // Timer set to 10 minutes (600000)
// //unsigned long timerDelay = 600000;
// // Set timer to 5 seconds (5000)
// unsigned long timerDelay = 5000;

// String sensorReadings;
// float sensorReadingsArr[3];

// void setup() {
//   Serial.begin(9600);
//   // Serial2.begin(9600, SERIAL_8N1, 9, 10);

//   WiFi.begin(ssid, password);
//   // Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     // Serial.print(".");
//   }
//   // Serial.println("");
//   // Serial.print("Connected to WiFi network with IP Address: ");
//   // Serial.println(WiFi.localIP());
 
//   // Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
// }

// void loop() {
//   Serial.print("Connecting.");
//   delay(1000);
// }

////////////////////////////////////////////////////////////////////////////
#include "EspMQTTClient.h"
#include "ArduinoJson.h"
#include <HardwareSerial.h>

unsigned long test = 0;

EspMQTTClient client(
  "Mmildcws",
  "Mmildcws",
  "broker.hivemq.com",  // MQTT Broker server ip
  "",                   // Can be omitted if not needed
  "",                   // Can be omitted if not needed
  ""                    // Client name that uniquely identify your device
                        // The MQTT port, default to 1883. this line can be omitted
);

void setup() {
  Serial.begin(115200);
  client.enableDebuggingMessages();                                           // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater();                                              // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA();                                                         // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("start", "start");  // You can activate the retain flag by setting the third parameter to true
}


void onConnectionEstablished() {
  // Serial.println("connect");
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("fibo/log", [](const String & payload) {
  Serial.print(payload+".");  
  // delay(2000);
  });

  // client.subscribe("v1/devices/me/rpc/request/+", [](const String& payload) {
  //   // Serial.println(payload);
  //   DynamicJsonDocument doc(1024);
  //   deserializeJson(doc, payload);
  //   String m = doc["method"];
  //   String p = doc["params"];
  //   if (m == "lamp1") {
  //     if (p == "true") {
  //       digitalWrite(32, 1);
  //     } else {
  //       digitalWrite(32, 0);
  //     }
  //   } else if (m == "lamp2") {
  //     if (p == "true") {
  //       digitalWrite(33, 1);
  //     } else {
  //       digitalWrite(33, 0);
  //     }
  //   } else if (m = "lamp3") {
  //     if (p == "true") {
  //       digitalWrite(25, 1);
  //     } else {
  //       digitalWrite(25, 0);
  //     }
  //   }

  //   Serial.println(p);
  // });

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial

  // client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
  //   Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  // });

  // Publish a message to "mytopic/test"
  // client.publish("iot", string(ACCurrentValue)); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions

  // client.executeDelayed(5 * 1000, []() {
  //   client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
  // });
}



void loop() {

  // unsigned long currentMillis = millis();

  if (millis() - test > 1000) {
    // float ACCurrentValue = readACCurrentValue();
    client.loop();
    // client.publish("iot", String(ACCurrentValue));

    test = millis();
  }
}