#include "config.h"

/**
     This function gets called every tick of the main loop.
*/
void Pomodomo::onTick() {
  // Serial.println("Tick");

  // If running and not paused, then ...
  if (running && !paused) {
    // If we hit the limit, stop running
    if (millis() > limit) {
      running = false;
    }
  }

  // Process blink period
  if (blinkLimit < millis()) {
    blinkLimit = millis() + BLINK_TIME;
    blinkState = !blinkState;
  }

  // Based on running, blinkState and paused, set the corresponding strip color
  if (!running) {
    blinkState ? setStripColor(ledStrip, pomodoro ? COLOR_POMODORO : COLOR_BREAK) : setStripColor(ledStrip, COLOR_NONE);
  } else {
    paused ? setStripColor(ledStrip, COLOR_PAUSE) : setStripColor(ledStrip, pomodoro ? COLOR_POMODORO : COLOR_BREAK);
  }
}
