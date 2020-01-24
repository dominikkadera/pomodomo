#include "config.h"
#include <FastLED.h>
#include <WiFi.h>

class Pomodomo {
  private:
    boolean lastButtonState = false;
    boolean debouncedButtonState = false;
    unsigned long debounceTime = 0;
    unsigned long limit = 0;
    unsigned long pauseStartMillis = 0;
    byte blocksCount = 0;
    boolean running = false;
    boolean paused = false;
    boolean pomodoro = false;
    unsigned long blinkLimit = 0;
    boolean blinkState = false;
  public:
    void readInput();
    void onTick();
    void onReleased();
    void onPressed();
    CRGB ledStrip[NUM_LEDS];
};

Pomodomo * pomodomo = new Pomodomo();

void setup() {
  // Serial.begin(115200);
  delay(STARTUP_SANITY_DELAY);
  FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(pomodomo->ledStrip, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  setStripColor(pomodomo->ledStrip, CRGB::Lime);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  pomodomo->readInput();
  pomodomo->onTick();  
}
