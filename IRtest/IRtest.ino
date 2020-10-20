#include <IRrecv.h>
#include <IRsend.h>
#include <M5Stack.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
const uint16_t kRecvPin = 3; //受信ピンの指定
const uint16_t kIrLed = 2; //送信ピンの指定
IRrecv irrecv(kRecvPin); //指定ピンへの受信
IRsend irsend(kIrLed);//指定ピンからの送信
decode_results results;//出てきた結果
int x = 0;
int y = 0;
int IRdata = 0;
int selecttime = 0;

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200);
  irrecv.enableIRIn(); //Start the receiver受信開始
  irsend.begin();
  while (!Serial)  //Wait for the serial connection to be establised.
  delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin "); //受信の実行とIRメッセージがピンから来るのを待つ
  Serial.println(kRecvPin); //ピンの表示
  irrecv.resume();  // Receive the next value
}
void loop() {
 x = Serial.read();
 if( x != -1 ){
 switch( x ){ 
  case 'R':
  Serial.println("受信開始");
  irrecive_func();
   Serial.println("終わった");
  break;
  case 'S':
  Serial.println("送信開始");
  irsend_func();
  break;
 }
 }
 delay(200);
}
