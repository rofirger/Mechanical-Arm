#include <ESP8266WiFi.h>
 
const char* ssid     = "shan_ku_pao_lu";
const char* password = "12345678";
                                            
void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  int i = 0;                                   
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);                                                  
    Serial.print(i++); Serial.print(' ');    
  }
  pinMode(2, OUTPUT);                                           
}
char msg[1024] = {'\0'};
const char* host = "192.168.4.22";
const int port = 80;
void loop() 
{
  WiFiClient tcpclient;
  while (!tcpclient.connect(host, port))
  {
    Serial.println("connection failed");        // 如果连接失败，则打印连接失败信息，并返回
    delay(500);
  }
  while(1)
  {
    digitalWrite(2, LOW);
    delay(300);
    digitalWrite(2, HIGH);
    delay(300);  
  }
}
