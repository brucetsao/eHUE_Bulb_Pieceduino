// Which pin on the Arduino is connected to the NeoPixels?
#define WSPIN            7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
#define RxPin      7
#define TxPin      6
#define _Debug 1
#define TestLed 1
#include <String.h>
#define CheckColorDelayTime 200
#define initDelayTime 2000
#define CommandDelay 100
#define commandlength 11
#define commandhead '@'
#define commandtail '#'
int CheckColor[][3] = {
                          {255 , 255,255} ,
                          {255 , 0,0} ,
                          {0 , 255,0} ,
                          {0 , 0,255} ,
                          {255 , 128,64} ,
                          {255 , 255,0} ,
                          {0 , 255,255} ,
                          {255 , 0,255} ,
                          {255 , 255,255} ,
                          {255 , 128,0} ,
                          {255 , 128,128} ,
                          {128 , 255,255} ,
                          {128 , 128,192} ,
                          {0 , 128,255} ,
                          {255 , 0,128} ,
                          {128 , 64,64} ,
                          {0 , 0,0} } ;
                     
                          




