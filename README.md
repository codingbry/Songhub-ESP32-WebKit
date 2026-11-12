# SongHub ESP32 BLE Remote

This project is firmware for a SongHub remote control built with an **original ESP32 DevKit / ESP32-WROOM-32** board.

The remote reads buttons arranged in a 4-row by 5-column keypad and sends commands to a computer over Bluetooth Low Energy (BLE) as keyboard and media-control keys.

## Important: ESP32 model

This project is written for an original ESP32 board, usually shown as **ESP32 DevKit**, **ESP32 Dev Module**, or **ESP32-WROOM-32**.

Do **not** use an ESP32-C3, ESP32-S2, ESP32-S3, or ESP8266 unless the firmware is changed for that board. The wiring in this guide is specifically for the original ESP32.

## What is included

- `Songhub-ESP32.ino` - the main firmware source code
- `config.h` - button layout, GPIO wiring, BLE passkey, and timing settings
- `platformio.ini` - PlatformIO build settings and required libraries

## What the client needs

### Hardware

- 1 × original ESP32 DevKit / ESP32-WROOM-32
- 20 keypad wires, or a 4 × 5 button matrix
- USB data cable
- Computer with Bluetooth, for pairing and testing

The ESP32 can be powered and programmed through USB. No external power supply is needed for initial testing.

### Software

1. Install [Visual Studio Code](https://code.visualstudio.com/).
2. Open Visual Studio Code.
3. Open the Extensions view using the square icon on the left side.
4. Search for **PlatformIO IDE** and install it.
5. Restart Visual Studio Code if PlatformIO asks you to.

The first build may download the ESP32 platform, compiler, Arduino framework, and libraries. This can take several minutes and requires an internet connection.

## Open the project

1. Download or copy this entire project folder to the computer.
2. In Visual Studio Code, choose **File → Open Folder**.
3. Select the folder containing `platformio.ini`.
4. Wait for PlatformIO to finish loading.

Do not open only the `.ino` file. Open the folder containing `platformio.ini` so PlatformIO can find all project settings and libraries.

## Build the firmware

The build checks the code and creates firmware files. The ESP32 does not need to be connected for this step.

1. Open the PlatformIO panel using the alien-head icon on the left.
2. Expand **Project Tasks**.
3. Expand **esp32dev**.
4. Click **Build**.

A successful build ends with a message similar to:

```text
SUCCESS
```

The generated firmware files are placed in the `.pio` folder. These files are normally not edited manually.

## Connect the keypad

Connect the keypad matrix as follows:

| Keypad wire | ESP32 GPIO |
|---|---:|
| Row 1 | GPIO13 |
| Row 2 | GPIO14 |
| Row 3 | GPIO16 |
| Row 4 | GPIO17 |
| Column 1 | GPIO18 |
| Column 2 | GPIO19 |
| Column 3 | GPIO21 |
| Column 4 | GPIO22 |
| Column 5 | GPIO23 |

The buttons are arranged in this order:

| Row | Buttons, from left to right |
|---|---|
| 1 | BGV, 1, 2, 3, Melody |
| 2 | Volume+, 4, 5, 6, Tempo+ |
| 3 | Volume-, 7, 8, 9, Tempo- |
| 4 | Next, Stop, 0, Play/Pause, Reserve |

Double-check the wiring before powering the board. Do not connect a GPIO pin to 5 V. The ESP32 uses 3.3 V logic.

## Upload the firmware

Only do this after the ESP32 is connected by a USB **data** cable.

1. Connect the ESP32 to the computer.
2. In Visual Studio Code, open the PlatformIO panel.
3. Expand **Project Tasks → esp32dev**.
4. Click **Upload**.
5. If PlatformIO asks for a serial port, select the port belonging to the ESP32.

If the upload stops at `Connecting.....`, hold the **BOOT** button on the ESP32 while the upload starts, then release it when the upload begins.

If the upload fails at the high upload speed, open `platformio.ini` and change:

```ini
upload_speed = 921600
```

to:

```ini
upload_speed = 115200
```

Then try **Upload** again.

## Pair the remote over Bluetooth

After uploading:

1. Disconnect and reconnect the ESP32, or press its reset button.
2. Open Bluetooth settings on the computer.
3. Look for **SongHub ESP32 Remote**.
4. Select it and choose **Pair** or **Connect**.
5. If a passkey is requested, enter `123456`.

The passkey is defined in `config.h`. Change it before deployment if the remote will be shared or used in a public place.

The remote must be connected over Bluetooth before button presses can send commands.

## Button actions

| Button | Action sent |
|---|---|
| 0–9 | Keyboard number |
| Volume+ / Volume- | System volume up / down |
| Next | Next media track |
| Play/Pause | Play or pause media |
| BGV | F13 |
| Melody | F14 |
| Tempo+ | F15 |
| Tempo- | F16 |
| Stop | F17 |
| Reserve | F18 |

The SongHub computer software should be configured to respond to F13 through F18 for the custom actions.

## Serial monitor

This firmware does not currently print diagnostic messages, but the serial monitor can still be opened for future versions.

- Baud rate: `115200`
- PlatformIO panel: **Project Tasks → esp32dev → Monitor**

## Troubleshooting

### PlatformIO cannot find the ESP32 platform

Build once while connected to the internet. PlatformIO should download the required Espressif32 platform and Arduino framework automatically. If it does not, open PlatformIO Home, select **Platforms**, search for **Espressif 32**, and install it.

### No serial port appears

- Make sure the USB cable supports data, not charging only.
- Disconnect and reconnect the ESP32.
- Install the USB driver required by the board's USB chip. Common chips are CP210x and CH340.
- Close other programs that may already be using the serial port.

### Upload fails

- Try a different USB cable or USB port.
- Press and hold **BOOT** while starting the upload.
- Reduce `upload_speed` to `115200`.
- Confirm that the selected board is an original ESP32 DevKit/WROOM-32.

### Bluetooth pairing works but buttons do nothing

- Confirm that the remote is connected, not merely visible.
- Check the keypad wiring against the table above.
- Confirm that the row and column wires were not swapped.
- Check that the SongHub software is listening for the expected number keys, media keys, and F13–F18.

## Current limitations

- Deep sleep is disabled.
- The firmware has not been tested on the physical enclosure or keypad in this source-only handoff.
- The original ESP32-C3 binary and this source project use different board families and wiring; they are not interchangeable.

---

# Tagalog na Gabay

## SongHub ESP32 BLE Remote

Ang project na ito ay firmware para sa SongHub remote control. Gumagamit ito ng **original ESP32 DevKit / ESP32-WROOM-32**.

Binabasa ng remote ang mga button na nakaayos sa 4 na row at 5 na column. Nagpapadala ito ng mga command sa computer gamit ang Bluetooth Low Energy (BLE), tulad ng keyboard at media-control keys.

## Mahalagang impormasyon tungkol sa ESP32

Ang project na ito ay para sa original ESP32. Maaaring makita ang pangalan nito bilang:

- ESP32 DevKit
- ESP32 Dev Module
- ESP32-WROOM-32

Huwag gumamit ng ESP32-C3, ESP32-S2, ESP32-S3, o ESP8266 maliban kung babaguhin ang firmware. Para sa original ESP32 lamang ang wiring sa gabay na ito.

## Mga file sa project

- `Songhub-ESP32.ino` - pangunahing source code
- `config.h` - button layout, GPIO wiring, BLE passkey, at timing settings
- `platformio.ini` - build settings at mga library na kailangan

## Mga kailangan ng client

### Hardware

- 1 × original ESP32 DevKit / ESP32-WROOM-32
- 20 keypad wire, o 4 × 5 button matrix
- USB data cable
- Computer na may Bluetooth

Maaaring paganahin at i-program ang ESP32 gamit ang USB. Hindi kailangan ng ibang power supply para sa unang testing.

### Software

1. I-install ang [Visual Studio Code](https://code.visualstudio.com/).
2. Buksan ang Visual Studio Code.
3. Buksan ang Extensions gamit ang square icon sa kaliwa.
4. Hanapin ang **PlatformIO IDE** at i-install ito.
5. I-restart ang Visual Studio Code kung hihingin ito ng PlatformIO.

Sa unang build, maaaring mag-download ang PlatformIO ng ESP32 platform, compiler, Arduino framework, at libraries. Maaaring tumagal ito ng ilang minuto at kailangan ng internet connection.

## Pagbukas ng project

1. I-download o kopyahin ang buong project folder sa computer.
2. Sa Visual Studio Code, piliin ang **File → Open Folder**.
3. Piliin ang folder na may `platformio.ini`.
4. Hintaying matapos mag-load ang PlatformIO.

Huwag ang `.ino` file lamang ang buksan. Kailangang buong folder ang buksan para makita ng PlatformIO ang lahat ng settings at libraries.

## Pag-build ng firmware

Sinusuri ng build ang code at gumagawa ng firmware files. Hindi kailangang nakakonekta ang ESP32 para sa step na ito.

1. Buksan ang PlatformIO panel gamit ang alien-head icon sa kaliwa.
2. I-expand ang **Project Tasks**.
3. I-expand ang **esp32dev**.
4. I-click ang **Build**.

Kapag successful, dapat may mensaheng katulad nito:

```text
SUCCESS
```

Ang firmware files ay ilalagay sa `.pio` folder. Karaniwang hindi kailangang baguhin ang mga file na ito.

## Pagkonekta ng keypad

Ikonekta ang keypad matrix ayon sa table:

| Keypad wire | ESP32 GPIO |
|---|---:|
| Row 1 | GPIO13 |
| Row 2 | GPIO14 |
| Row 3 | GPIO16 |
| Row 4 | GPIO17 |
| Column 1 | GPIO18 |
| Column 2 | GPIO19 |
| Column 3 | GPIO21 |
| Column 4 | GPIO22 |
| Column 5 | GPIO23 |

Ang ayos ng mga button ay:

| Row | Mga button, mula kaliwa pakanan |
|---|---|
| 1 | BGV, 1, 2, 3, Melody |
| 2 | Volume+, 4, 5, 6, Tempo+ |
| 3 | Volume-, 7, 8, 9, Tempo- |
| 4 | Next, Stop, 0, Play/Pause, Reserve |

Suriing mabuti ang wiring bago paganahin ang board. Huwag ikonekta ang GPIO pin sa 5 V. Ang ESP32 ay gumagamit ng 3.3 V logic.

## Pag-upload ng firmware

Gawin lamang ito kapag nakakonekta ang ESP32 gamit ang USB **data** cable.

1. Ikonekta ang ESP32 sa computer.
2. Buksan ang PlatformIO panel sa Visual Studio Code.
3. I-expand ang **Project Tasks → esp32dev**.
4. I-click ang **Upload**.
5. Kung humingi ng serial port ang PlatformIO, piliin ang port ng ESP32.

Kung huminto sa `Connecting.....`, pindutin nang matagal ang **BOOT** button habang nagsisimula ang upload. Bitawan ito kapag nagsimula na ang upload.

Kung pumalya ang upload sa mataas na speed, buksan ang `platformio.ini` at palitan:

```ini
upload_speed = 921600
```

ng:

```ini
upload_speed = 115200
```

Pagkatapos, subukang muli ang **Upload**.

## Pag-pair ng remote sa Bluetooth

Pagkatapos ng upload:

1. I-disconnect at ikonekta muli ang ESP32, o pindutin ang reset button.
2. Buksan ang Bluetooth settings sa computer.
3. Hanapin ang **SongHub ESP32 Remote**.
4. Piliin ito at pindutin ang **Pair** o **Connect**.
5. Kung humingi ng passkey, ilagay ang `123456`.

Ang passkey ay nasa `config.h`. Palitan ito bago gamitin sa aktwal na deployment kung ibabahagi ang remote o gagamitin sa pampublikong lugar.

Kailangang connected sa Bluetooth ang remote bago gumana ang mga button.

## Mga action ng button

| Button | Ipinapadalang action |
|---|---|
| 0–9 | Keyboard number |
| Volume+ / Volume- | Lakasan / hinaan ang system volume |
| Next | Susunod na media track |
| Play/Pause | Play o pause ng media |
| BGV | F13 |
| Melody | F14 |
| Tempo+ | F15 |
| Tempo- | F16 |
| Stop | F17 |
| Reserve | F18 |

Dapat naka-configure ang SongHub computer software na tumanggap ng F13 hanggang F18 para sa custom actions.

## Serial monitor

Wala pang diagnostic messages ang firmware na ito, pero maaaring buksan ang serial monitor para sa mga susunod na version.

- Baud rate: `115200`
- PlatformIO panel: **Project Tasks → esp32dev → Monitor**

## Troubleshooting

### Hindi makita ng PlatformIO ang ESP32 platform

Mag-build habang nakakonekta sa internet. Dapat awtomatikong i-download ng PlatformIO ang Espressif32 platform at Arduino framework. Kung hindi ito mangyari, buksan ang PlatformIO Home, piliin ang **Platforms**, hanapin ang **Espressif 32**, at i-install ito.

### Walang lumalabas na serial port

- Siguraduhing data cable ang USB cable, hindi charging-only cable.
- I-disconnect at ikonekta muli ang ESP32.
- I-install ang USB driver ng board. Karaniwang CP210x o CH340 ang ginagamit.
- Isara ang ibang program na gumagamit ng serial port.

### Pumapalya ang upload

- Subukan ang ibang USB cable o USB port.
- Pindutin nang matagal ang **BOOT** habang nagsisimula ang upload.
- Gawing `115200` ang `upload_speed`.
- Siguraduhing original ESP32 DevKit/WROOM-32 ang board.

### Nakapaired ang Bluetooth pero walang ginagawa ang button

- Siguraduhing connected ang remote, hindi lamang nakikita sa listahan.
- Suriin ang keypad wiring ayon sa table.
- Tiyaking hindi nagkapalit ang row at column wires.
- Tiyaking nakikinig ang SongHub software sa number keys, media keys, at F13–F18.

## Mga kasalukuyang limitasyon

- Naka-disable ang deep sleep.
- Hindi pa nasusubukan ang firmware sa aktwal na enclosure o keypad sa source-only handoff na ito.
- Magkaibang board family at wiring ang original ESP32-C3 binary at ang source project na ito. Hindi sila interchangeable.

