#include "config.h"

boolean readButtonState() {
  return (digitalRead(BUTTON_PIN) == LOW);
}

// Optimization for cases when setStripColor gets called with the same color again
CRGB lastColor = CRGB::Black;

void setStripColor(CRGB * ledStrip, CRGB color) {
  if(lastColor == color) {
    return;
  }
  for(int i = 0; i < NUM_LEDS; ++i) {
    ledStrip[i] = color;
  }
  FastLED.show();
  lastColor = color;
}
