# Firmware Architecture Guide

LoverBoy's firmware (`firmware/LoverBoy/`) is organized by responsibility: a core orchestrator delegates to focused managers, and every game inherits a common lifecycle from a base class.

[Português](./FIRMWARE-pt.md) · [Architecture](#01-architecture) · [Features](#02-features) · [Code Structure](#03-code-structure) · [Adding a Game](#04-adding-a-game) · [Back to README](../README.md)

---

## 01. Architecture

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

---

## 02. Features

- **Included games:** Crossy, Flappy, Frogger, Genius, Snake, and Tetris at ~60 FPS.
- **Delta rendering (zero flicker):** Only the pixels that changed between frames are erased and redrawn, which removes flicker on the display bus.
- **Persistent highscores:** Top 3 per game saved to Flash (Preferences/NVS), with a classic arcade-style 3-initial entry screen.
- **In-game tutorials:** Every game has a tutorial screen on its 3-option title carousel (Play, Tutorial, Highscores), in English and Brazilian Portuguese.
- **Settings menu:** Volume, screen brightness, color theme (5 palettes), language, and highscore reset. The mute state persists across reboots, so the buzzer never blares at startup.
- **Multi-language UI:** English (default) and Brazilian Portuguese. Every on-screen string lives in one table (`i18n_strings.h`).
- **Non-blocking audio:** Background melodies and sound effects run on a state machine without freezing game logic.

---

## 03. Code Structure

```text
firmware/LoverBoy/
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

Pin definitions live in [`pins.h`](../firmware/LoverBoy/src/core/pins.h); the matching PCB mapping is in the [PCB documentation](../pcb/README.md#04-pinout--firmware-mapping).

---

## 04. Adding a Game

1. Create `XxxGame.h/.cpp` in `src/games/`, inheriting from `Game` and implementing its pure virtual methods (`resetGame`, `updatePlaying`, `drawPlaying`, `handleInputPlaying`, `onResume`, `drawTutorialContent`).
2. Add a `case` for it in `LoverBoyCore::loadGame()`.
3. Add its name to `gameNames` and bump `GAME_COUNT` in [`MenuManager.h`](../firmware/LoverBoy/src/ui/MenuManager.h). Use a single-word name.
4. Add its tutorial strings for every language to `i18n_strings.h`.
