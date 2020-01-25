#include "config.h"

/**
   This function gets called when the button is pressed.
*/
void Pomodomo::onPressed() {
  // Serial.println("Pressed");
  // If the timer is running, then ...
  if (running) {
    // If in pomodoro (breaks can't be paused)
    if (pomodoro) {
      // If not paused, we're pausing now, so store the current millis
      if (!paused) {
        sendRequest(POMODORO_PAUSE_START_URL);
        pauseStartMillis = millis();
      }
      // Else we're ending the pause now, so add the time span of the pause to the limit
      else {
        sendRequest(POMODORO_PAUSE_END_URL);
        limit += (millis() - pauseStartMillis);
      }
      // Toggle pause
      paused = !paused;
    }
  }
  // Else we're waiting for the approval to the new period
  else {

    // If the last period was Pomodoro, then ...
    if (pomodoro) {

      // Notify
      sendRequest(POMODORO_END_URL);

      // Increment blocksCount
      ++blocksCount;

      // If the long break limit hit, then ...
      if (blocksCount >= LONG_BREAK_AFTER) {

        // Reset the blocksCount
        blocksCount = 0;

        // Set the long break limit to the counter
        limit = millis() + LONG_BREAK_MILLIS;

      }
      // Else set the short break limit to the counter
      else {
        limit = millis() + SHORT_BREAK_MILLIS;
      }
    }
    // Else the break has ended, so set the pomodoro limit to the counter
    else {
      // Notify
      sendRequest(POMODORO_START_URL);
      limit = millis() + POMODORO_MILLIS;
    }

    // Flip the pomodoro and start counting again
    pomodoro = !pomodoro;
    running = true;

  }
}
