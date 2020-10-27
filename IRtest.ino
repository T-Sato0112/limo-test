#include <M5Stack.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include <BLEDevice.h> // BLEデバイス宣言   
#include <BLEServer.h>  
#include <BLEUtils.h>
#include <BLE2902.h>
#include <IRtext.h>
#include <IRac.h>

const uint16_t kCaptureBufferSize = 1024;
const uint32_t kBaudRate = 115200;
#if DECODE_AC
const uint8_t kTimeout = 50;
#else   // DECODE_AC
const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;
#define LEGACY_TIMING_INFO false


//IRsetting
const uint16_t kRecvPin = 22; //受信ピンの指定
const uint16_t kIrLed = 21; //送信ピンの指定
IRsend irsend(kIrLed);//指定ピンからの送信
IRrecv irrecv(kRecvPin);
decode_results results;//出てきた結果

int x = 0;
int y = 0;
int IRdata = 0;
int selecttime = 0;
int waitcount;

uint16_t *rawData;        // IR message container
uint16_t dataLength = 0;  // IR message length

void setup() { 
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.print("Setup ....");
  initBLE();
  irrecv.enableIRIn(); //Start the receiver受信開始
  irsend.begin();
  while (!Serial)  //Wait for the serial connection to be establised.
  delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin "); //受信の実行とIRメッセージがピンから来るのを待つ
  Serial.println(kRecvPin); //ピンの表示
  
  
}
void loop() {
 M5.update();
 loopBLE();
//================後で消す=====================// 
 x = Serial.read(); //これから何を実行するか
 if( x != -1 ){ //xが0じゃない場合ここを進行 x初期値0
 switch( x ){ //x に入力された内容により操作変更
//赤外線受信
  case 'R'://Rの場合赤外線受信
     irrecv.enableIRIn(); //Start the receiver受信開始
     while (!Serial)
     Serial.println("受信開始");
     irrecive_func(); //赤外線受信タブへ移動
     Serial.print(IRdata);
     Serial.println("このデータを保存しました");
     x = 0;//xを0にしループ循環
  break;

//赤外線送信
  case 'S'://Sが入力された場合赤外線送信
     Serial.println("送信開始");
     irsend_func();//赤外線送信タブへ移動
     Serial.println("このデータを送信しました"); 
     x = 0;//xを0にしループ循環
  break;
 }//switch
 }//if
 delay(200);
 //==========================================================//
}// void
