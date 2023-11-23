/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-TFTM050A2-2 with Capacitive Touch Panel 
Display is Hardward SPI 4-Wire SPI Interface and 5V Power Supply
Capacitive Touch Panel is I2C Interface
Tested and worked with:
Works with Arduino 1.6.0 IDE 
****************************************************/
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#define RA8875_INT 4
#define RA8875_CS 10
#define RA8875_RESET 9
Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;     // time for next update
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// SoftwareSerial link(15, 14);  //Rx, Tx
// String receive = "{\"allunit\":\"0\"}";
String receive ;


// receive = '{"allunit":"0"}';

//#include "Temperature.h"

#define PI 3.1415926535897932384626433832795
#define Temp 10
int a = 1000, b = 3500;
int n, f;
int j, j2 , lj;
int i, i2 , li;
int pct = 0;
int d[5] = {20, 20, 20, 20, 20};
uint16_t col[5] = {0x7006, 0xF986, 0x6905, 0x7FF7, 0x024D};
char str[12];
const char text[4] = "mild";



void setup() {
  //  tft.reset(); -not an RA8875 member name
  Serial.begin(115200);
  Serial3.begin(115200);
  tft.begin(RA8875_480x272);
  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.textMode();
  // tft.setTextColor(0x00F0);
  // tft.textTransparent(0x00F0);
  // tft.textColor(0x1000,0xF010);
  // tft.setTextColor(0x00F0,0xFFE0);
  
  //tft.textTransparent(RA8875_RED);
  tft.setTextSize(200);  

}

void loop() {
  
  
  //Serial.println(receive);
  


  // Serial.println((char*)receive);
  
  // tft.textWrite(text,sizeof(text));
  

  //  tft.drawBitmap(350, 70, 10, 70, 180, 120);// - not an adafruitra8875 function
  //tft.fillCircle(385, 213, 25, RA8875_RED);
  // tft.drawLine(100,100,0,100,RA8875_RED);

  // for (int p = 0; p < 4000; p++) {
  //   j = 120 * (sin(PI * p / 2000)); i = 120 * (cos(PI * p / 2000)); j2 = 110 * (sin(PI * p / 2000)); i2 = 110 * (cos(PI * p / 2000)); tft.drawLine(i2 + 160, j2 + 160, i + 160, j + 160, RA8875_BLUE);
  // }
  // if (b > a)

  //   while (a < b) {
      
  //     j = 120 * (sin(PI * a / 2000));k
  //     i = 120 * (cos(PI * a / 2000));
  //     j2 = 110 * (sin(PI * a / 2000));
  //     i2 = 110 * (cos(PI * a / 2000));
  //     tft.drawLine(i2 + 160, j2 + 160, i + 160, j + 160, RA8875_RED);
  //     tft.fillCircle(160, 150, 50, 0xffff);
  //     tft.setTextSize(4);
  //     tft.setTextColor(0x0000);
  //     tft.setCursor(135, 145);
  //     tft.print(a / 40); tft.print("%"); delay(20);

  //     for (uint16_t c = 0; c < 13; c++) {
  //       tft.drawLine(378 + c, 213, 378 + c, (200 - a / 40), RA8875_RED);
  //     }       //200=0 & 100=100
  //     for (uint16_t c = 0; c < 13; c++) {
  //       tft.drawLine(378, 213 + c, 378, (200 - a / 40) + c, RA8875_RED);
  //     }

  //     a++;
  //   } b = 0;
  // //}

  // //////////////////////////////////////////////////////////////////

  // while (b < a) {
  //   j = 120 * (sin(PI * a / 2000));
  //   i = 120 * (cos(PI * a / 2000));
  //   j2 = 110 * (sin(PI * a / 2000));
  //   i2 = 110 * (cos(PI * a / 2000));
  //   tft.drawLine(i2 + 160, j2 + 160, i + 160, j + 160, RA8875_RED);
  //   tft.fillCircle(160, 150, 50, 0xffff);
  //   tft.setTextSize(4);
  //   tft.setTextColor(0x0000);
  //   tft.setCursor(135, 145);
  //   tft.print(a / 40); tft.print("%"); delay(50);

  //   for (uint16_t c = 0; c < 13; c++) {
  //     tft.drawLine(378 + c, (200 - a / 40), 378 + c, 100, RA8875_RED);
  //   }       //200=0 & 100=100
  //   for (uint16_t c = 0; c < 13; c++) {
  //     tft.drawLine(378, (200 - a / 40) + c, 378, 100 + c, RA8875_RED);
  //   }

  //   a--;
  // }
  if (Serial3.available() > 0) {
  // Serial.println("test");
  receive = Serial3.readString();
  Serial.println(receive);
  // Serial.println(Serial3.read());
  StaticJsonDocument <500> doc;
  // DynamicJsonDocument doc(1024);
  deserializeJson(doc, receive );

  
  // String sensor = doc["allunit"];
  // Serial.println(receive);
  // String sum = ;
  Serial.println((doc["allunit"].as<String>()).length());
  int Sumallunit = (doc["allunit"].as<String>()).length();
  // JsonObject object = doc.to<JsonObject>();
  // Serial.println(object.size());
  // Serial.println(doc["allunit"].size());
  // Serial.println(sizeof(sum));
  const char *allunit = doc["allunit"];
  const char *allcost = doc["allcost"];
  
  const char *Lunit = doc["Lunit"];
  const char *Lcost = doc["Lcost"];
  const char *B1unit = doc["B1unit"];
  const char *B1cost = doc["B1cost"];
  const char *B2unit = doc["B2unit"];
  const char *B2cost = doc["B2cost"];

  tft.fillScreen(RA8875_WHITE);
  //tft.setRotation(1);
  tft.textColor(RA8875_BLACK,RA8875_WHITE);
  tft.textSetCursor(170, 30);
  tft.textWrite("Electricity bill",16);
  tft.textColor(RA8875_MAGENTA,RA8875_WHITE);
  tft.textSetCursor(180, 50); 
  tft.textWrite("Unit : ",7);
  tft.textWrite(allunit,(doc["allunit"].as<String>()).length());
  tft.textSetCursor(180, 70);
  tft.textWrite("Cost : ",7);
  tft.textWrite(allcost,(doc["allcost"].as<String>()).length());

  tft.textColor(RA8875_BLACK,RA8875_WHITE);
  tft.textSetCursor(10, 120);
  tft.textWrite("Living room",11);
  tft.textColor(RA8875_MAGENTA,RA8875_WHITE);
  tft.textSetCursor(10, 140); 
  tft.textWrite("Unit : ",7);
  tft.textWrite(Lunit,(doc["Lunit"].as<String>()).length());
  tft.textSetCursor(10, 160);
  tft.textWrite("Cost : ",7);
  tft.textWrite(Lcost,(doc["Lcost"].as<String>()).length());

  tft.textColor(RA8875_BLACK,RA8875_WHITE);
  tft.textSetCursor(160, 120);
  tft.textWrite("Bed room 1",10);
  tft.textColor(RA8875_MAGENTA,RA8875_WHITE);
  tft.textSetCursor(160, 140); 
  tft.textWrite("Unit : ",7);
  tft.textWrite(B1unit,(doc["B1unit"].as<String>()).length());
  tft.textSetCursor(160, 160);
  tft.textWrite("Cost : ",7);
  tft.textWrite(B1cost,(doc["B1cost"].as<String>()).length());

  tft.textColor(RA8875_BLACK,RA8875_WHITE);
  tft.textSetCursor(330, 120);
  tft.textWrite("Bed room 2",10);
  tft.textColor(RA8875_MAGENTA,RA8875_WHITE);
  tft.textSetCursor(330, 140); 
  tft.textWrite("Unit : ",7);
  tft.textWrite(B2unit,(doc["B2unit"].as<String>()).length());
  tft.textSetCursor(330, 160);
  tft.textWrite("Cost : ",7);
  tft.textWrite(B2cost,(doc["B2cost"].as<String>()).length());

  }
}