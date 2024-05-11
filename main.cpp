#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define REFRESHTIME 15
#define BASEDELAY 20

struct Pixel
{
  uint32_t color;
  int delay;
};
Pixel pixelData[LED_COUNT];

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t Yellow = pixels.Color(6 * BRIGHTNESS, 3 * BRIGHTNESS, 0);
uint32_t Amber = pixels.Color(6 * BRIGHTNESS, 2 * BRIGHTNESS, 0);
uint32_t Orange = pixels.Color(6 * BRIGHTNESS, 1 * BRIGHTNESS, 0);
uint32_t OrangeDark = pixels.Color(5 * BRIGHTNESS, 1 * BRIGHTNESS, 0);
uint32_t OrangeDarker = pixels.Color(4 * BRIGHTNESS, 1 * BRIGHTNESS, 0);
uint32_t OrangeDarkest = pixels.Color(3 * BRIGHTNESS, 1 * BRIGHTNESS, 0);
uint32_t Black = pixels.Color(0, 0, 0);

uint32_t Colors[] = {Yellow, Amber, Orange, OrangeDark, OrangeDarker, OrangeDarkest};

void setup()
{
  pixels.begin();
  randomSeed(analogRead(0));

  for (int i = 0; i < LED_COUNT; i++)
  {
    pixelData[i].color = Colors[random(0, 6)];
    pixelData[i].delay = random(BASEDELAY * 5, BASEDELAY * 10);

    pixels.setPixelColor(i, pixelData[i].color);
  }
}

void loop()
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    if (--pixelData[i].delay > 0)
      continue;

    pixelData[i].color = pixelData[i].color == Black
                             ? Colors[random(0, 6)]
                             : Black;
    pixelData[i].delay = random(BASEDELAY, BASEDELAY * 2);

    pixels.setPixelColor(i, pixelData[i].color);
  }

  pixels.show();
  delay(REFRESHTIME);
}