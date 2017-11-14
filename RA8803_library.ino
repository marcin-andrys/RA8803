#include "RA8803.hpp"
#include "RA8803.cpp"

RA8803<LcdBus> display(320,48);

uint32_t cnt;
void setup()
{

  Serial.begin(115200);
  Serial.println("Initialization...");
	display.init();
  display.clear();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.setTextColor(1);
  display.println("test");
  display.display();
  Serial.println("Initialized");
  delay(1000);
}

void loop()
{
  display.clear();
  display.setCursor(100,8);
  display.println("licznik");
  cnt++;
  display.setCursor(125,24);
  display.println(cnt);
  display.display();
  delay(250);
}
