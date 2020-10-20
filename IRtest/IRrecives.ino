
int i = 0;
void irrecive_func(){

 while(y == 0){
  if (irrecv.decode(&results)&& results.decode_type == 3) //信号が受信した場合の動作かつでコードタイプ３の場合
  {  
    serialPrintUint64(results.value, HEX);//取得した信号を16進に変更
    Serial.println("");//前回の信号の変換
    Serial.print(resultToHumanReadableBasic(&results));//信号詳細受信
    Serial.println(results.decode_type);
    IRdata = results.value;
    Serial.println("ok?this signal 1or2 ");  
    i = Serial.read();  
    delay(6000);
    Serial.println(i);
    if( i != -1 ){ 
    Serial.println("ifの中");
     irrecv.resume();  // Receive the next value
    switch(i){
      case 'A':
       selecttime = 1;
       y = 1;
      Serial.print("設定保存");
      break;
      case 'B':
      Serial.print("やり直し");
       y = 0; 
      break;
      default:
       Serial.println(i);
      break ;
      }//switch
    }
  }//data type if
}//while if
}//void 
