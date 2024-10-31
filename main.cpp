#include "Arduino.h"
#include <SPI.h> // 加载SPI库
#include <Wire.h> // 加载Wire库
#include <Adafruit_GFX.h> // 加载Adafruit_GFX库
#include <Adafruit_SSD1306.h> // 加载Adafruit_SSD1306库
#include "RF24.h"

// 定义 OLED屏幕的分辨率
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
RF24 myRadio (7, 8);
const byte address[6] = "00001";
String data;
void setup() {
  Serial.begin(115200); // 设置串口波特率
  Serial.println("OLED FeatherWing test"); // 串口输出
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // 设置OLED的I2C地址
  myRadio.begin();
  myRadio.openReadingPipe(0, address);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.startListening();
  Serial.print("jieshou Setup Initialized");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // 设置OLED的I2C地址
  display.setTextSize(1); // 设置字体大小
  display.setTextColor(SSD1306_WHITE); // 设置字体颜色
  display.setCursor(0,0); // 设置开始显示文字的坐标
  display.println("!@#$%^&*123456qazxswedc\n1234567890"); // 输出的字符
  delay(200);
  display.display(); // 使更改的显示生效
  delay(100);
}
void loop() {
  if (myRadio.available()) 
  {
    char text[8] = "";
    myRadio.read(&text, sizeof(text));
    Serial.println(text);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println(text);
    display.display();
    delay(200);
  }

}