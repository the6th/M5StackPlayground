#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// @see https://blog.rogiken.org/blog/2018/04/11/esp32%E3%81%A7bluetoothserial%E9%80%9A%E4%BF%A1%E3%82%92%E3%81%97%E3%82%88%E3%81%86%EF%BC%81/


BluetoothSerial SerialBT; void setup() {
  Serial.begin(115200);
  SerialBT.begin("testESP32");

  Serial.println("BluetoothSerial start");
} int sendIBT(String str) {
  int len = str.length();
  int i;
  uint8_t arr[len];
  for (i = 0; i < len; i++) arr[i] = (uint8_t)str.charAt(i);
  SerialBT.write(arr, len);
  return 0;
} int i = 0;
void loop() {
  i++;
  sendIBT("num: " + String(i) + "\n");
  delay(10);
}
