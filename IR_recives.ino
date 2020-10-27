//================================IRrecive=====================================//
void irrecive_func() { //受信呼び出し関数
  y = 0;// whileでループさせるため0代入
  delay(1000);
  Serial.println("setup now ");
  delay(1000);
  Serial.print("Pleasewait");
  for ( waitcount = 0 ; waitcount <= 2; waitcount++) { //初期値0 2以上でループ通貨 1後から足していく
    Serial.print("．");
    delay(500);
  }
  Serial.println();
  Serial.println("Ready to receive");
  Serial.println("Waiting send signal");
  while (y == 0) { //y=0の時ループ
    if (irrecv.decode(&results)) { //irrecv.decodeがenableの時　つまり信号があるとき　scanfとかで使う&と同じ理論 これだとresultsの中のirrcv.decode
      if (results.decode_type == 3) { // decode type3の時これ後で変更
        rawData = resultToRawArray(&results);         // 信号データを抽出
        dataLength = getCorrectedRawLength(&results); // 配列長を抽出
        Serial.printf("rawData[%d] : ", dataLength);
        IRdata = results.value;
        irrecv.resume();  // Receive the next value
        y = 1;
        if (results.overflow)
          rawData = resultToRawArray(&results);         // 信号データを抽出
        dataLength = getCorrectedRawLength(&results); // 配列長を抽出
        String description = IRAcUtils::resultAcToString(&results);
        for (int i = 0; i < dataLength; i++) {
          Serial.printf("%d, ", rawData[i]);
        }
      }
    }
    delay(1000);
  }
}//void
//========================================================================//

//==============================IRsend====================================//
void irsend_func() {
  if (dataLength > 0) {
    Serial.printf("send rawData[%d]\n", dataLength);
    irsend.sendRaw(rawData, dataLength, 38);
  } else {
    Serial.println("rawData[] is empty. Skip sending");
  }
}
//========================================================================//
