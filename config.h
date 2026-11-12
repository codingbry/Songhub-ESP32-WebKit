#pragma once

// ESP32 DevKit / ESP32-WROOM-32 pin assignment.
// GPIO6-GPIO11 are reserved for the module's SPI flash and must not be used.
static const uint8_t ROW_PINS[4] = {13, 14, 16, 17};
static const uint8_t COL_PINS[5] = {18, 19, 21, 22, 23};

// Matrix layout, left to right and top to bottom.
static const char KEYMAP[4][5] = {
  {'B', '1', '2', '3', 'M'},
  {'V', '4', '5', '6', 'T'},
  {'v', '7', '8', '9', 't'},
  {'N', 'S', '0', 'P', 'R'},
};

// BLE pairing passkey. Change this before deployment if the remote is shared.
static const uint32_t BLE_PASSKEY = 123456;

// The original C3 binary used a separate activation flow. This first ESP32
// build uses the BLE pairing passkey above and does not store an application PIN.
// Keep deep sleep disabled until wake-button behavior is tested on the actual
// enclosure and matrix wiring.
static const bool ENABLE_DEEP_SLEEP = false;
static const uint32_t DEEP_SLEEP_AFTER_MS = 10UL * 60UL * 1000UL;
static const uint16_t KEY_DEBOUNCE_MS = 35;

