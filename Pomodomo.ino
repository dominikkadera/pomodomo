#include "config.h"
#include "secret.h"
#include <FastLED.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Declare here, so it can be used where needed
void setStripColor(CRGB * ledStrip, CRGB color);

// Root CA
const char * root_ca = \
                       "-----BEGIN CERTIFICATE-----\n" \
                       "MIICiTCCAg+gAwIBAgIQH0evqmIAcFBUTAGem2OZKjAKBggqhkjOPQQDAzCBhTEL\n" \
                       "MAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UE\n" \
                       "BxMHU2FsZm9yZDEaMBgGA1UEChMRQ09NT0RPIENBIExpbWl0ZWQxKzApBgNVBAMT\n" \
                       "IkNPTU9ETyBFQ0MgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMDgwMzA2MDAw\n" \
                       "MDAwWhcNMzgwMTE4MjM1OTU5WjCBhTELMAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdy\n" \
                       "ZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgGA1UEChMRQ09N\n" \
                       "T0RPIENBIExpbWl0ZWQxKzApBgNVBAMTIkNPTU9ETyBFQ0MgQ2VydGlmaWNhdGlv\n" \
                       "biBBdXRob3JpdHkwdjAQBgcqhkjOPQIBBgUrgQQAIgNiAAQDR3svdcmCFYX7deSR\n" \
                       "FtSrYpn1PlILBs5BAH+X4QokPB0BBO490o0JlwzgdeT6+3eKKvUDYEs2ixYjFq0J\n" \
                       "cfRK9ChQtP6IHG4/bC8vCVlbpVsLM5niwz2J+Wos77LTBumjQjBAMB0GA1UdDgQW\n" \
                       "BBR1cacZSBm8nZ3qQUfflMRId5nTeTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/\n" \
                       "BAUwAwEB/zAKBggqhkjOPQQDAwNoADBlAjEA7wNbeqy3eApyt4jf/7VGFAkK+qDm\n" \
                       "fQjGGoe9GKhzvSbKYAydzpmfz1wPMOG+FDHqAjAU9JM8SaczepBGR7NjfRObTrdv\n" \
                       "GDeAU/7dIOA1mjbRxwG55tzd8/8dLDoWV9mSOdY=\n" \
                       "-----END CERTIFICATE-----\n";

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
    void sendRequest(const char * url) {
      setStripColor(ledStrip, CRGB::Yellow);
      if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;
        http.begin(url, root_ca);
        http.GET();
        http.end();
      }
    }
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
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Connect to WiFi, max 40 * 250 = 10000 ms = 10 seconds timeout
  for (int i = 0; i < 40; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    } else {
      delay(250);
    }
  }
  setClock();
}

void loop() {
  pomodomo->readInput();
  pomodomo->onTick();
}
