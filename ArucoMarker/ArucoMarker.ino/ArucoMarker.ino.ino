#include <M5Stack.h>

struct Marker {
  int square[5][5];
  int id;
};

Marker marker = {
  {
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 1, 1, 1},
  },
  1
};

// the setup routine runs once when M5Stack starts up
void setup() {

  // initialize the M5Stack object
  M5.begin();
  M5.Lcd.fillScreen(WHITE);


  aruco(marker);


}

// the loop routine runs over and over again forever
void loop() {


}
void aruco(Marker m) {
  M5.Lcd.fillRect(55, 15, 210, 210, BLACK);
  for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j)
      _fill(i, j, m.square[j][i]);
}
void _fill(int x, int y, int b) {

  M5.Lcd.fillRect((x * 30) + 85, (y * 30) + 45, 30, 30, b == 1 ? WHITE : BLACK );
}

