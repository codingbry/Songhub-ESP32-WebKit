#include <Arduino.h>
#include <Keypad.h>
#include <BleKeyboard.h>
#include "config.h"

BleKeyboard bleKeyboard("SongHub ESP32 Remote", "MPJ Electronics", 100);
Keypad keypad(makeKeymap(KEYMAP), (byte*)ROW_PINS, (byte*)COL_PINS, 4, 5);

static unsigned long lastActivity = 0;

static void sendFunctionKey(uint8_t key) {
  if (!bleKeyboard.isConnected()) return;
  bleKeyboard.write(key);
}

static void sendMediaKey(uint8_t key) {
  if (!bleKeyboard.isConnected()) return;
  bleKeyboard.write(key);
}

static void handleKey(char key) {
  lastActivity = millis();
  if (!bleKeyboard.isConnected()) return;

  if (key >= '0' && key <= '9') {
    bleKeyboard.write(key);
    return;
  }

  // Standard consumer keys remain compatible with the normal operating-system
  // media controls. F13-F18 provide stable custom actions for SongHub.
  switch (key) {
    case 'B': sendFunctionKey(KEY_F13); break; // BGV
    case 'M': sendFunctionKey(KEY_F14); break; // Melody
    case 'V': sendMediaKey(KEY_MEDIA_VOLUME_UP); break;
    case 'v': sendMediaKey(KEY_MEDIA_VOLUME_DOWN); break;
    case 'T': sendFunctionKey(KEY_F15); break; // Tempo+
    case 't': sendFunctionKey(KEY_F16); break; // Tempo-
    case 'N': sendMediaKey(KEY_MEDIA_NEXT_TRACK); break;
    case 'S': sendFunctionKey(KEY_F17); break; // Stop
    case 'P': sendMediaKey(KEY_MEDIA_PLAY_PAUSE); break;
    case 'R': sendFunctionKey(KEY_F18); break; // Reserve
  }
}

static void keypadEvent(KeypadEvent key) {
  if (keypad.getState() == PRESSED) handleKey((char)key);
}

static void maybeSleep() {
  if (!ENABLE_DEEP_SLEEP || !bleKeyboard.isConnected()) return;
  if (millis() - lastActivity < DEEP_SLEEP_AFTER_MS) return;
  // Deep sleep is intentionally left as a tested follow-up: a matrix has
  // several possible wake lines and waking on a held key needs debouncing.
}

void setup() {
  lastActivity = millis();
  keypad.setDebounceTime(KEY_DEBOUNCE_MS);
  keypad.addEventListener(keypadEvent);

  // BLEKeyboard uses the ESP32 BLE stack and provides the pairing passkey API
  // in current releases of the library.
  bleKeyboard.setPassKey(BLE_PASSKEY);
  bleKeyboard.begin();
}

void loop() {
  keypad.getKeys();
  maybeSleep();
  delay(2);
}

