# Build & Upload Guide

Three ways to compile the firmware and flash the LILYGO T-Display-S3. All use the board FQBN `esp32:esp32:lilygo_t_display_s3`.

[Português](./BUILDING-pt.md) · [Linux](#01-native-linux-arduino-cli) · [Windows](#02-native-windows-arduino-ide) · [WSL](#03-wsl-terminal-build_and_uploadsh) · [Back to README](../README.md)

---

## 01. Native Linux (`arduino-cli`)

Ideal for standalone Linux environments.

```bash
# Compile
arduino-cli compile --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy

# Upload (adjust -p to your device port)
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy
```

---

## 02. Native Windows (Arduino IDE)

Ideal for Windows users who prefer a graphical interface.

1. **Board support:** Install **ESP32** board support in the Boards Manager.
2. **Libraries:** Install the **TFT_eSPI** library by Bodmer.
3. **Display configuration:** In `TFT_eSPI/User_Setup_Select.h`, uncomment `#include <User_Setups/Setup206_LilyGo_T_Display_S3.h>`.
4. **Compile & upload:** Open `firmware/LoverBoy/LoverBoy.ino`, select the **LilyGo T-Display-S3** board and the matching `COMx` port, then click **Upload**.

---

## 03. WSL Terminal (`build_and_upload.sh`)

Ideal for developers working inside a WSL (Linux) terminal on Windows. The script compiles with `arduino-cli` in WSL, stages the binaries, and flashes them with the Windows `esptool.exe`.

```bash
./build_and_upload.sh -p COM7
```

| Flag | Description | Default |
|---|---|---|
| `-p`, `--port <PORT>` | Target serial port on the Windows host | `COM7` |
| `-b`, `--baud <BAUD>` | Upload baud rate | `921600` |
| `-f`, `--fqbn <FQBN>` | Board identifier | `esp32:esp32:lilygo_t_display_s3` |
| `-d`, `--dir <DIR>` | Firmware directory | `firmware/LoverBoy` |
| `-c`, `--cli <PATH>` | `arduino-cli` binary in WSL | auto-detected |
| `-e`, `--esptool <PATH>` | `esptool.exe` path on Windows | auto-detected |
| `-h`, `--help` | Show help and exit | |
