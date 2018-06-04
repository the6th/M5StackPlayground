#include <M5Stack.h>
#include "sys/time.h"

#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLEBeacon.h"
#include "esp_sleep.h"

#define GPIO_DEEP_SLEEP_DURATION     10  // sleep x seconds and then wake up
RTC_DATA_ATTR static time_t last;        // remember last boot in RTC Memory
RTC_DATA_ATTR static uint32_t bootcount; // remember number of boots in RTC Memory

#ifdef __cplusplus
extern "C" {
#endif

uint8_t temprature_sens_read();
//uint8_t g_phyFuns;

#ifdef __cplusplus
}
#endif

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
BLEAdvertising *pAdvertising;
struct timeval now;

//#define BEACON_UUID           "8ec76ea3-6668-48da-9866-75be8bc86f4d" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
#define BEACON_UUID           "2f234454-cf6d-4a0f-adf2-f4911ba9ffa6" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
#define BEACON_UUID_REV       "a6ffa91b-91f4-f2ad-0f4a-6dcf5444232f"


/*
   Draw Aruco Marker
   author: twitter@keshin_sky
*/
struct Marker {
  int id;
  int square[5][5];

};

Marker marker[3]  = {
  { 1,
    {
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 1, 1, 1},
    }
  },
  {
    2,
    {
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {0, 1, 0, 0, 1},
    }
  },
  {
    3,
    {
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
    }
  }

};


void setBeacon(int minid) {

  Serial.printf("start BeaconB %d\n", minid);
  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID_REV));
  oBeacon.setMajor(1);
  oBeacon.setMinor(minid);
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();

  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04

  std::string strServiceData = "";

  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData();
  oAdvertisementData.addData(strServiceData);

  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);

}

// the setup routine runs once when M5Stack starts up
void setup() {

  // initialize the M5Stack object
  M5.begin();
  M5.Lcd.clear();


  gettimeofday(&now, NULL);

  Serial.printf("start ESP32 %d\n", bootcount++);

  Serial.printf("deep sleep (%lds since last reset, %lds since last boot)\n", now.tv_sec, now.tv_sec - last);

  last = now.tv_sec;

  // Create the BLE Device
  BLEDevice::init("");

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();

  pAdvertising = pServer->getAdvertising();

  sendBeacon(1);

}

// the loop routine runs over and over again forever
void loop() {
  buttons_test();
 M5.update();

  delay(100);
}
void buttons_test() {
  if (M5.BtnA.wasPressed()) {
    aruco(marker[0]);

  }
  if (M5.BtnB.wasPressed()) {
    aruco(marker[1]);
  }
  if (M5.BtnC.wasPressed()) {
    aruco(marker[2]);
  }
}
void aruco(Marker m) {

  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.fillRect(55, 15, 210, 210, BLACK);
  for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j)
      _fill(i, j, m.square[j][i]);
  M5.Lcd.setCursor(5, 220);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println(m.id);
  sendBeacon(m.id);
}
void sendBeacon(int minid) {

  Serial.printf("start BeaconA %d\n", minid);
  setBeacon(minid);
  // Start advertising
  pAdvertising->start();
  Serial.println("Advertizing started...");
  delay(1000);
  pAdvertising->stop();
   Serial.println("Advertizing stop");
}
void _fill(int x, int y, int b) {
  M5.Lcd.fillRect((x * 30) + 85, (y * 30) + 45, 30, 30, b == 1 ? WHITE : BLACK );
}

