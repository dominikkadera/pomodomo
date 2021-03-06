#define POMODORO_MILLIS           1200000   // 20 minutes = 20 * 60 * 1000
#define SHORT_BREAK_MILLIS        300000    //  5 minutes =  5 * 60 * 1000
#define LONG_BREAK_MILLIS         900000    // 15 minutes = 15 * 60 * 1000
#define LONG_BREAK_AFTER          4
#define LED_PIN                   27
#define LED_BRIGHTNESS            10
#define BUTTON_PIN                5
#define BUTTON_DEBOUNCE_MS        50
#define NUM_LEDS                  16
#define COLOR_ORDER               GRB
#define STARTUP_SANITY_DELAY      2000
#define BLINK_TIME                400
#define COLOR_BREAK               CRGB::White
#define COLOR_POMODORO            CRGB::Blue
#define COLOR_PAUSE               CRGB::Red
#define COLOR_NONE                CRGB::Black
#define COLOR_CONNECTING          CRGB::Lime
#define COLOR_SENDING             CRGB::Yellow
#define COLOR_CONNECTION_FAILED   CRGB::Purple
#define WIFI_CONNECTION_CHECKS    40   // max 40 * 250 = 10000 ms = 10 seconds timeout
#define WIFI_CHECK_DELAY          250  // .........^^^
#define FAIL_NOTIFICATION_LENGTH  1000 // 1 second
