#include <M5Stack.h>
#include <WiFi.h>

// the setup routine runs once when M5Stack starts up
void setup(){

    // Initialize the M5Stack object
    M5.begin();

    // LCD display
    M5.Lcd.printf("Wi-Fi SSID Scanner");

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

}

// the loop routine runs over and over again forever
void loop() {

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    if (n == 0) {
        M5.Lcd.println("no networks found");
    } else {
        M5.Lcd.print(n);
        M5.Lcd.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            M5.Lcd.print(i + 1);
            M5.Lcd.print(": ");
            M5.Lcd.print(WiFi.SSID(i));
            M5.Lcd.print(" ");
            M5.Lcd.print(WiFi.channel(i));
            M5.Lcd.print("CH");
            M5.Lcd.print(" (");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.print(")");
            M5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }

    // Wait a bit before scanning again
    delay(5000);
}

