# LoverBoy - Custom PCB & Electronics

[![EDA: EasyEDA v6.5](https://img.shields.io/badge/EDA-EasyEDA%20v6.5-blue.svg)](source/)
[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-lightgrey.svg)](../LICENSE)

[← LoverBoy](../README.md) · **Language:** English | [Português](README-pt.md)

A single-layer through-hole carrier board designed in EasyEDA that integrates the **LILYGO T-Display-S3**, 8 tactile arcade buttons (D-Pad, A, B, Start, Select), a passive piezo buzzer, a power slide switch, and a TP4056 USB-C LiPo charging circuit onto one handheld PCB.

> [!WARNING]
> **Hardware Rev 1.0 Errata (Known Issues):**
> The current `v1.0` board files in this folder contain two known hardware errata that are scheduled to be fixed in the upcoming **v2.0 PCB redesign**:
> 1. **Button Pull-Down Routing Short ([Issue #7](https://github.com/paixonite/loverboy/issues/7)):** A routing mistake causes the push buttons to short `3V3` to `GND` when pressed instead of routing through the `10kΩ` resistors (`R1–R8`). On fabricated `v1.0` boards, this is remediated by cutting the direct trace behind each button and soldering a bridge through the resistor.
> 2. **TP4056 Footprint Offset ([Issue #8](https://github.com/paixonite/loverboy/issues/8)):** The TP4056 module footprint is ~2 mm narrower horizontally than the physical module, causing the module to slightly overhang the board edge and shifting the display ~2 mm left of center in the `v1.0` enclosure ([Issue #9](https://github.com/paixonite/loverboy/issues/9)).

> [!NOTE]
> **File Naming (`EspBoy`):** Hardware Revision 1.0 was originally designed and prototyped under the working title *EspBoy* before the project was officially named **LoverBoy**. All `v1.0` source, schematic, BOM, and Gerber files retain the `EspBoy_*` prefix; the upcoming `v2.0` hardware release will transition to `LoverBoy_*`.

## Board Layout & Schematic

<p align="center">
  <img src="EspBoy_PCB_Layout.png" width="48%" alt="LoverBoy PCB Layout" />
  <img src="EspBoy_Schematic.png" width="48%" alt="LoverBoy Schematic" />
</p>

- **Vector PDFs for Inspection / Printing:**
  - [`EspBoy_PCB_Layout.pdf`](EspBoy_PCB_Layout.pdf)
  - [`EspBoy_Schematic.pdf`](EspBoy_Schematic.pdf)

## Bill of Materials (BOM)

The full spreadsheet is available in [`EspBoy_BOM.csv`](EspBoy_BOM.csv).

| Designator | Component | Qty | Footprint / Package | Part Number | LCSC Code |
| :--- | :--- | :---: | :--- | :--- | :--- |
| `ESPBOY` | **LILYGO T-Display-S3** (ESP32-S3 + 1.9" TFT) | 1 | Custom THT Header | T-Display S3 | — |
| `UP, DOWN, LEFT, RIGHT, A, B, START, SELECT` | **12×12mm Tactile Push Button** | 8 | `KEY-TH_4P-L12.0-W12.0` | `TC-00121FS-080E` | `C4355204` |
| `R1–R8` | **10kΩ Axial Resistor** | 8 | `RES-TH_BD2.2-L6.0-P10.00` | `10kΩ` (Axial 0.4) | `C9900020985` |
| `BUZZER` | **Passive Piezo Buzzer** (22mm diameter, 10mm pitch) | 1 | `BUZ-TH_BD22.0-P10.00` | `2207-P10MM` | `C49246969` |
| `SWITCH` | **Slide Switch** (Power ON/OFF) | 1 | `SW-TH_SS12F44G4` | `SS12F44G5` | `C22435641` |
| `USB-C` | **TP4056 USB-C Charging Module** | 1 | Custom THT Module | TP4056 1S LiPo | — |
| *(External)* | **3.7V LiPo Battery** | 1 | Wired to TP4056 `BAT+`/`BAT-` | 3.7V Rechargeable LiPo | — |

## Pinout & Firmware Mapping

All PCB traces map directly to the definitions in [`firmware/LoverBoy/src/core/pins.h`](../firmware/LoverBoy/src/core/pins.h):

| PCB Designator | Function | ESP32-S3 GPIO | Firmware Macro (`pins.h`) | Notes |
| :--- | :--- | :---: | :--- | :--- |
| `UP` | D-Pad Up | `GPIO 1` | `BTN_UP` | Active HIGH (10kΩ pull-down) |
| `RIGHT` | D-Pad Right | `GPIO 2` | `BTN_RIGHT` | Active HIGH (10kΩ pull-down) |
| `DOWN` | D-Pad Down | `GPIO 3` | `BTN_DOWN` | Active HIGH (10kΩ pull-down) |
| `LEFT` | D-Pad Left | `GPIO 43` | `BTN_LEFT` | Active HIGH (10kΩ pull-down) |
| `SELECT` | Select Button | `GPIO 18` | `BTN_SELECT` | Active HIGH (10kΩ pull-down) |
| `START` | Start Button | `GPIO 44` | `BTN_START` | Active HIGH (10kΩ pull-down) |
| `A` | Action Button A | `GPIO 17` | `BTN_A` | Active HIGH (10kΩ pull-down) |
| `B` | Action Button B | `GPIO 21` | `BTN_B` | Active HIGH (10kΩ pull-down) |
| `BUZZER` | Passive Piezo Audio | `GPIO 16` | `BUZZER_PIN` | Driven via LEDC PWM timer |
| *(Internal)* | Battery Power Enable | `GPIO 15` | `POWER_ENABLE_PIN` | Internal T-Display-S3 power latch |
| *(Internal)* | Battery ADC Sense | `GPIO 4` | `BATTERY_SENSE_PIN` | Internal voltage divider ADC |
| *(Internal)* | TFT Backlight PWM | `GPIO 38` | `TFT_BL_PIN` | Internal 1.9" ST7789 backlight |

## Manufacturing & Fabrication Guide

The board was designed with generous trace widths and clearances so it can be produced either **in-house at a maker space** or ordered from a **commercial PCB fab house** using the exact same files.

### Option 1: In-House Maker Space Fabrication (CNC Milling / Laser)

The `v1.0` prototype was manufactured in-house on a **CNC PCB milling machine**, and the layout is equally suited for **laser PCB fabrication** (laser resist ablation + etching or direct copper ablation):

- **Single-Layer Routing (Bottom Layer):** All copper traces are routed on the bottom layer, meaning in-house fabrication requires zero board flipping or two-sided alignment.
- **Wide Clearances & Traces:** Designed around physical isolation milling tolerances (≥ 0.4 mm clearance and wide traces), meaning it will effortlessly resolve on both CNC routers and finer-spot laser machines.
- **Through-Hole (THT) Components Only:** Every component on the carrier board is through-hole, making hand-soldering on bare copper (without solder mask) straightforward.
- **No Plated Through-Holes (PTH) Needed:** Because routing is strictly single-sided, no chemical via electroplating or copper eyelets/rivets are required.

### Option 2: Commercial PCB Fab (JLCPCB / PCBWay / OSH Park)

To order professionally fabricated boards with solder mask, upload [`gerbers/Gerber_EspBoy_PCB_EspBoy_2025-10-09.zip`](gerbers/Gerber_EspBoy_PCB_EspBoy_2025-10-09.zip) directly to your fab house of choice with these standard settings:

| Parameter | Recommended Setting |
| :--- | :--- |
| **Base Material** | FR-4 |
| **Layers** | 1 or 2 Layers (2 Layers is standard minimum pricing) |
| **PCB Thickness** | **1.6 mm** (matches the [3D printed enclosure](../case/README.md) clamping ribs) |
| **Copper Weight** | 1 oz |
| **Surface Finish** | HASL (with lead), Lead-Free HASL, or ENIG |
| **Solder Mask** | Any color |

## Editing the Source Files (EasyEDA)

The editable schematic and PCB layout live in [`source/`](source/):
- `source/SCH_EspBoy.json` — Schematic file
- `source/PCB_EspBoy.json` — PCB layout file

### How to Open

1. Open **[EasyEDA Standard](https://easyeda.com/editor)** (browser or desktop app, created in `v6.5.51`).
2. Go to **File → Open → EasyEDA...**
3. Select `SCH_EspBoy.json` and `PCB_EspBoy.json` to inspect, edit traces, or export updated Gerbers.

## Directory Structure

```text
pcb/
├── README.md                                       # This documentation (English)
├── README-pt.md                                    # Portuguese documentation
├── EspBoy_BOM.csv                                  # Bill of Materials with LCSC part numbers
├── EspBoy_PCB_Layout.pdf / .png                    # 2D board layout exports
├── EspBoy_Schematic.pdf / .png                     # Circuit schematic exports
├── gerbers/
│   └── Gerber_EspBoy_PCB_EspBoy_2025-10-09.zip     # Fabrication-ready Gerber & Excellon drill archive
└── source/
    ├── PCB_EspBoy.json                             # EasyEDA Standard PCB layout source
    └── SCH_EspBoy.json                             # EasyEDA Standard schematic source
```
