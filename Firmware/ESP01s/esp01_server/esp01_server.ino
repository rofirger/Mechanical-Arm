//服务端
#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>

#define TX  1
#define RX  3
//自定义串口 (RX, TX)
//SoftwareSerial MySerial(RX, TX);
#define AP_ssid   "shan_ku_pao_lu"
#define password  "12345678"
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);
WiFiServer wifiServer(80);
static String comdata = "";

void setup() 
{
  Serial.begin(115200);
  // 开启串口服务
  //MySerial.begin(115200);
  //MySerial.listen();
  delay(1000);
  //配置接入点信息
  WiFi.mode(WIFI_AP);
  //配置接入点的IP，网关IP，子网掩码
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_ssid, password, 3, 0);
  wifiServer.begin();
  // 初始化LED
  pinMode(LED_BUILTIN, OUTPUT);
}
char msg[1024] = {'\0'};
void loop() 
{
  static bool _led_status = false;
  WiFiClient client = wifiServer.available();
  if (client) 
  {
    while (1)
    {
      while (Serial.available() > 0)
      {
        int len = Serial.read(msg, 1024);
        msg[len] = '\0';
        comdata += msg;
        Serial.println(comdata);
        client.print(comdata);//将socket客户端接收的数据发送回去
        comdata = "";
        digitalWrite(LED_BUILTIN, _led_status);
        _led_status = !_led_status;
      }
    }

    client.stop();
  }
}
