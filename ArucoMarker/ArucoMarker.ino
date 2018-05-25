#include <M5Stack.h>

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

// the setup routine runs once when M5Stack starts up
void setup() {

  // initialize the M5Stack object
  M5.begin();
  M5.Lcd.clear();
  aruco(marker[0]);
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
}
void _fill(int x, int y, int b) {
  M5.Lcd.fillRect((x * 30) + 85, (y * 30) + 45, 30, 30, b == 1 ? WHITE : BLACK );
}

