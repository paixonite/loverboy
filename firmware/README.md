# LoverBoy - Firmware

[![Platform: ESP32-S3](https://img.shields.io/badge/platform-ESP32--S3-blue.svg)](#-code-structure)
[![Framework: Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)](#-build--upload)

**Language:** English | [Português](./README-pt.md)

LoverBoy's C++ firmware (`firmware/LoverBoy/`) is organized by responsibility: a core orchestrator delegates to focused managers, and every game inherits a common lifecycle from an abstract base class.

## ▸ Architecture

`LoverBoyCore` is the global state orchestrator (Menu vs Game) and delegates to specialized managers:

| Manager | Responsibility |
|---|---|
| `InputManager` | Centralized button reading: asymmetric zero-latency press detection, continuous-LOW release qualification (prevents double clicks), DAS/ARR auto-repeat, and state-transition consumption |
| `MenuManager` | Splash screen, game carousel, settings UI, and HUD |
| `BatteryManager` | ADC read and piecewise battery percentage calculation |
| `ConfigManager` | Centralized NVS persistence (settings, mute state, highscores) |
| `SoundManager` | Non-blocking audio queue and melody player (millisecond state machine) |
| `TextRenderer` | UTF-8 text renderer that overlays accents on the retro pixel font |
| `Localization` | Language selection and string lookup via `tr()` |

New games inherit from the abstract `Game` superclass, which provides the standard state machine and template methods (Template Method pattern).

## ▸ Features

- **Included games:** Crossy, Flappy, Frogger, Genius, Snake, and Tetris at ~60 FPS.
- **Delta rendering (zero flicker):** Only the pixels that changed between frames are erased and redrawn, which removes flicker on the display bus.
- **Persistent highscores:** Top 3 per game saved to Flash (Preferences/NVS), with a classic arcade-style 3-initial entry screen.
- **In-game tutorials:** Every game has a tutorial screen on its 3-option title carousel (Play, Tutorial, Highscores), in English and Brazilian Portuguese.
- **Settings menu:** Volume, screen brightness, color theme (5 palettes), language, and highscore reset. The mute state persists across reboots, so the buzzer never blares at startup.
- **Multi-language UI:** English (default) and Brazilian Portuguese. Every on-screen string lives in one table (`i18n_strings.h`).
- **Non-blocking audio:** Background melodies and sound effects run on a state machine without freezing game logic.

## ▸ Code Structure

```text
firmware/
├── README.md                           # This documentation (English)
├── README-pt.md                        # Portuguese documentation
└── LoverBoy/
    ├── LoverBoy.ino                    # Entry point: initializes system and runs loop
    └── src/
        ├── core/                       # Core system managers & hardware abstraction
        │   ├── LoverBoyCore.h/.cpp     # Global state orchestrator (Menu vs Game)
        │   ├── InputManager.h/.cpp     # Button debounce, edge detection, auto-repeat
        │   ├── BatteryManager.h/.cpp   # ADC read & battery percentage calculation
        │   ├── ConfigManager.h/.cpp    # Centralized NVS configuration persistence
        │   ├── SoundManager.h/.cpp     # Non-blocking audio queue & melody player
        │   ├── pins.h                  # Hardware pin mappings for ESP32-S3 & display
        │   └── audio_assets.h          # Frequency library and game melody arrays
        ├── games/                      # Game engine & playable games
        │   ├── Game.h/.cpp             # Abstract base class (Template Method lifecycle)
        │   ├── CrossyGame.h/.cpp
        │   ├── FlappyGame.h/.cpp
        │   ├── FroggerGame.h/.cpp
        │   ├── GeniusGame.h/.cpp
        │   ├── SnakeGame.h/.cpp
        │   └── TetrisGame.h/.cpp
        ├── ui/                         # User interface & visual presentation
        │   ├── MenuManager.h/.cpp      # Splash, game carousel, settings & HUD
        │   ├── TextRenderer.h/.cpp     # UTF-8 text renderer with accent overlays
        │   └── Utf8Text.h/.cpp         # UTF-8 parsing and accent decomposition
        └── localization/               # Internationalization & translations
            ├── Localization.h/.cpp     # Language selector and string lookup (tr())
            └── i18n_strings.h          # Central string table for all languages
```

Pin definitions live in [`pins.h`](./LoverBoy/src/core/pins.h); the matching PCB mapping is in the [PCB documentation](../pcb/README.md#-pinout--firmware-mapping).

## ▸ Build & Upload

All three methods target the board FQBN `esp32:esp32:lilygo_t_display_s3`.

### Prerequisites (All Platforms)

1. **Board support:** Install the **ESP32** board core (`esp32:esp32`) via Arduino Boards Manager or `arduino-cli`.
2. **Display library:** Install **TFT_eSPI** by Bodmer.
3. **Display configuration:** In `TFT_eSPI/User_Setup_Select.h`, uncomment `#include <User_Setups/Setup206_LilyGo_T_Display_S3.h>`.

### Option 1: Native Linux (`arduino-cli`)

Ideal for standalone Linux environments:

```bash
# Compile
arduino-cli compile --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy

# Upload (adjust -p to your device port)
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy
```

### Option 2: Native Windows (Arduino IDE)

Ideal for Windows users who prefer a graphical interface:

1. Open `firmware/LoverBoy/LoverBoy.ino` in the Arduino IDE.
2. Select the **LilyGo T-Display-S3** board and the matching `COMx` port.
3. Click **Upload**.

### Option 3: WSL Terminal (`build_and_upload.sh`)

Ideal for developers working inside a WSL (Linux) terminal on Windows. The root [`build_and_upload.sh`](../build_and_upload.sh) script compiles with `arduino-cli` in WSL, stages the binaries, and flashes them with the Windows `esptool.exe`:

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

## ▸ Adding a Game

1. Create `XxxGame.h/.cpp` in [`src/games/`](./LoverBoy/src/games/), inheriting from `Game` and implementing its pure virtual methods (`resetGame`, `updatePlaying`, `drawPlaying`, `handleInputPlaying`, `onResume`, `drawTutorialContent`).
2. Add a `case` for it in `LoverBoyCore::loadGame()`.
3. Add its name to `gameNames` and bump `GAME_COUNT` in [`MenuManager.h`](./LoverBoy/src/ui/MenuManager.h). Use a single-word name.
4. Add its tutorial strings for every language to [`i18n_strings.h`](./LoverBoy/src/localization/i18n_strings.h).
