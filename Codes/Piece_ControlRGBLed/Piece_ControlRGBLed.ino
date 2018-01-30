#include "Pinset.h"
#include "pieceduino.h"
#define SSID        "Pru_HTCE5ED"
#define PASSWORD    "12345678"
pieceduino wifi(Serial1);
uint32_t len;

#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, WSPIN, NEO_GRB + NEO_KHZ800);

byte RedValue = 0, GreenValue = 0, BlueValue = 0;
String ReadStr = "      " ;
int delayval = 500; // delay for half a second

void setup() {
  // put your setup code here, to run once:
    Serial1.begin(115200);  //for pieceduino init wifi
   
  Serial.begin(9600) ;
   DebugMsgln("Program Start Here") ;
    wifi.begin();//初始化
  wifi.reset();//重啟WiFi
  wifi.setWifiMode(1);//將WiFi模組設定為Station模式
  wifi.connToWifi(SSID,PASSWORD);//連接網路
  Serial.println(wifi.getIP());//取得IP
  wifi.enableMUX();//開啟多人連線模式
  wifi.createTCPServer(80);//開啟TCP Server
   Serial.println(wifi.getIP());//取得IP
  pixels.begin(); // This initializes the NeoPixel library.
          DebugMsgln("init LED") ;
    ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
      DebugMsgln("Turn off LED") ;
      if (TestLed ==  1)
          {
               CheckLed() ;
                 DebugMsgln("Check LED") ;
                  ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
                  DebugMsgln("Turn off LED") ;
          }
 

    
 
     delay(initDelayTime) ;   //wait 2 seconds
     
}



void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() >0)
  {
    ReadStr = Serial.readStringUntil(0x23) ;    // read char @
     //  Serial.read() ;
      DebugMsg("ReadString is :(") ;
       DebugMsg(ReadStr) ;
       DebugMsg(")\n") ;
        if (DecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
           {
            DebugMsgln("Change RGB Led Color") ;
            ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
           }
  }

    len = wifi.recv();
  if(len){
    char recvData[len-1];
    for (uint32_t i = 0; i < len; i++) 
    {
      Serial.print("Recive ");
      Serial.print(i);
      Serial.print(" Byte: ");
      Serial.print(wifi.MessageBuffer[i]); 
      Serial.print("  From: ");
      Serial.println(wifi.client_id);
      recvData[i] = wifi.MessageBuffer[i];

    }
           ReadStr = String(recvData) ;
          if (DecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
           {
                DebugMsgln("Change RGB Led Color") ;
                ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
           }
  //  delay(1000);
    wifi.Send(wifi.client_id , "Hello This is Server" , 20);//送出訊息到Client端
  }
  //------------------------------------------
  
}

void ChangeBulbColor(int r,int g,int b)
{
      // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
   for(int i=0;i<NUMPIXELS;i++)
   {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
       // delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

boolean DecodeString(String INPStr, byte *r, byte *g , byte *b) 
{
                    Serial.print("check string:(") ;
                    Serial.print(INPStr) ;
                         Serial.print(")\n") ;

      int i = 0 ;
      int strsize = INPStr.length();
      for(i = 0 ; i <strsize ;i++)
          {
                    Serial.print(i) ;
                    Serial.print(":(") ;
                         Serial.print(INPStr.substring(i,i+1)) ;
                    Serial.print(")\n") ;

              if (INPStr.substring(i,i+1) == "@")
                  {
                    Serial.print("find @ at :(") ;
                    Serial.print(i) ;
                         Serial.print("/") ;
                              Serial.print(strsize-i-1) ;
                         Serial.print("/") ;
                              Serial.print(INPStr.substring(i+1,strsize)) ;
                    Serial.print(")\n") ;
                      *r = byte(INPStr.substring(i+1,i+1+3).toInt()) ;
                      *g = byte(INPStr.substring(i+1+3,i+1+3+3).toInt() ) ;
                      *b = byte(INPStr.substring(i+1+3+3,i+1+3+3+3).toInt() ) ;
                       Serial.print("convert into :(") ;
                        Serial.print(*r) ;
                         Serial.print("/") ;
                        Serial.print(*g) ;
                         Serial.print("/") ;
                        Serial.print(*b) ;
                         Serial.print(")\n") ;
                            
                      return true ;
                  }
          }
    return false ;

}
void CheckLed()
{
     for(int i = 0 ; i <16; i++)
        {
              ChangeBulbColor(CheckColor[i][0],CheckColor[i][1],CheckColor[i][2]) ;
              delay(CheckColorDelayTime) ;
        }
}
void DebugMsg(String msg)
{
    if (_Debug != 0)
        {
          Serial.print(msg) ;
        }
   
}
void DebugMsgln(String msg)
{
    if (_Debug != 0)
        {
          Serial.println(msg) ;
        }
   
}
