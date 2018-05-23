#include “BluetoothSerial.h”
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;void setup() {
Serial.begin(115200);
SerialBT.begin(“testESP32”);
Serial.println(“BluetoothSerial start”);
}int sendIBT(String str) {
int len = str.length();
int i;
uint8_t arr[len];
for (i = 0; i < len; i++) arr[i] = (uint8_t)str.charAt(i);
SerialBT.write(arr, len);
return 0;
}int i = 0;
void loop() {
i++;
sendIBT(“num:” + String(i) + “\n”);
delay(10);
}
