#include "pieceduino.h"

pieceduino wifi(Serial1);
uint32_t len;

String ReadStr = "      " ;
int delayval = 500; // delay for half a second

void setup() {
  // put your setup code here, to run once:
    Serial1.begin(115200);  //for pieceduino init wifi
   
  Serial.begin(9600) ;

    
    wifi.begin();//初始化
  wifi.reset();//重啟WiFi
  wifi.setWifiMode(2);//將WiFi模組設定為Access Point模式
  if (wifi.setAP("PieceDuino-AP","12345678",1,0)){
    Serial.println("Create AP Success");
    Serial.print("IP: ");       
    Serial.println(wifi.getIP());
  }else{
    Serial.println("Create AP Failure");
  }
  wifi.enableMUX();//開啟多人連線模式
  wifi.createTCPServer(8080);//開啟TCP Server
   Serial.println(wifi.getIP());//取得IP
     delay(2000) ;   //wait 2 seconds
     
}



void loop() {
  // put your main code here, to run repeatedly:

    len = wifi.recv();
    if (len > 0) 
    {
          Serial.print("Wifi Received data len is :(") ;
          Serial.print(len) ;
          Serial.print(")\n") ;
          Serial.print("Receive Data is :(");
          Serial.print(wifi.MessageBuffer) ;
          Serial.print(")\n") ;
          
    }
 
}

