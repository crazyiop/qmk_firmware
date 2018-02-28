//#include "rgblights.h"

#define LED_LEVEL   6

enum colors{
  RED = 0,
  BLUE,
  GREEN,
  YELLOW,
  NONE,
};

static int8_t led_level = 6;

void rgball(uint8_t color){
  switch (color)
  {
    case RED:
      rgblight_sethsv(0, 255, led_level * 171 / (LED_LEVEL + 1));
      break;
    case BLUE:
      rgblight_sethsv(191, 247, led_level * 196 / (LED_LEVEL + 1));
      break;
    case GREEN:
      rgblight_sethsv(135, 240, led_level * 166 / (LED_LEVEL + 1));
      break;
    case YELLOW:
      rgblight_sethsv(65, 234, led_level * 193 / (LED_LEVEL + 1));
      break;
    case NONE:
      rgblight_sethsv(0, 0, 0);
      break;
  }
}

