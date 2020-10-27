//==================================BLE===================================//
BLEServer *pServer = NULL;
BLECharacteristic * pNotifyCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
#define LOCAL_NAME                  "M5Stack-Smart-remo"
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID                "0619d5ea-155f-11eb-adc1-0242ac120002"
#define CHARACTERISTIC_UUID_RX      "0619d8ec-155f-11eb-adc1-0242ac120002"
#define CHARACTERISTIC_UUID_NOTIFY  "0619d9f0-155f-11eb-adc1-0242ac120002"

// Bluetooth LE Change Connect State
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

//============================Bluetooth LE Recive//======================================//
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) {
        String cmd = String(rxValue.c_str());
        Serial.print("Received Value: ");
        Serial.println(cmd);
        if (cmd == "RED")
        {
          
        }
        if (cmd == "YELLOW")
        {
          
        }
        if (cmd == "BLUE")
        {
        
        }
      }
    }
};
//========================================Bluetooth LE initialize===========================================//
void initBLE(){
  // Create the BLE Device デバイス名の宣言//
  BLEDevice::init(LOCAL_NAME);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pNotifyCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_NOTIFY,
                        BLECharacteristic::PROPERTY_NOTIFY
                        );
  
  pNotifyCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // 受信機側の存在発信 //
  pServer->getAdvertising()->start();  
}

// Bluetooth LE loop
void loopBLE() {
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("startAdvertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

//========================================================================// 
