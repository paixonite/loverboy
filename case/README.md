# 🖨️ LoverBoy - Enclosure & 3D Printing

[Versão em Português](./README-pt.md)

[![Onshape](https://img.shields.io/badge/CAD-Onshape-blue?logo=onshape)](https://cad.onshape.com/documents/1e7a1e5f646915cc7623cce0/w/f956c9933d51415f8580a5c6/e/0af3083584b46a6f4c513a5e?renderMode=0&uiState=6ae2d81bf7dd7a478c9b1770)

![LoverBoy Case Assembly](./renders/render_assembly.png)

A custom two-piece enclosure designed in Onshape for the **LoverBoy** portable game console. It holds the custom PCB, LILYGO T-Display-S3, tactile push buttons, buzzer, power slide switch, TP4056 USB-C charging board, and rechargeable LiPo battery into an ergonomic retro handheld form factor.

---

## 📸 Renders

<p align="center">
  <img src="./renders/render_front.png" width="48%" alt="Front Cover Render" />
  <img src="./renders/render_back.png" width="48%" alt="Back Cover Render" />
</p>

---

## 🔩 Hardware & Fasteners (BOM)

| Item | Quantity | Description | Notes |
| :--- | :---: | :--- | :--- |
| **M2 Screws** | 4 | M2 × 16mm (Pan head or Socket head) | Passes through the front cover into the back |
| **M2 Hex Nuts** | 4 | Standard M2 hex nuts | Seated in the slots in the back shell |

---

## ⚙️ 3D Printing Guidelines

The case is a very easy print at around 50g and 13x8cm in size.

| Parameter | Recommended Setting |
| :--- | :--- |
| **Material** | **PLA** (PETG also works well) |
| **Layer Height** | **0.20 mm** (or 0.16 mm for smoother exterior curves) |
| **Infill** | **15% – 20%** (Gyroid) |
| **Perimeters / Walls** | **3 walls** |
| **Print Orientation** | Print both shells **flat-side down** directly on the build plate |
| **Supports** | **None required!** Designed to print without any support material |

---

## 🛠️ Assembly Guide

1. **Insert M2 Nuts:** Place the 4x M2 hex nuts into their designated pockets inside the back cover.
2. **Mount PCB:** Place the assembled LoverBoy PCB into the front cover, close it with the rear cover.
3. **Fasten:** Insert the 4x M2 × 16mm screws through the front cover corner holes and thread them into the M2 nuts in the back cover.

---

## 📂 Directory Structure

```text
case/
|-- README.md                   # This documentation (English)
|-- README-pt.md                # Portuguese documentation
|-- source/
|   `-- assembly.step           # Universal STEP solid body assembly (CAD exchange)
|-- stl/
|   |-- front_cover.stl         # Slicer-ready front faceplate
|   `-- back_cover.stl          # Slicer-ready back shell
`-- renders/
    |-- render_assembly.png     # Full assembled case render
    |-- render_front.png        # Front cover render
    `-- render_back.png         # Back cover render
```

---

## 🌐 Onshape Source Model

The master parametric CAD model is maintained on **Onshape**:
- **Public Onshape Document:** [LoverBoy Case on Onshape](https://cad.onshape.com/documents/1e7a1e5f646915cc7623cce0/w/f956c9933d51415f8580a5c6/e/0af3083584b46a6f4c513a5e?renderMode=0&uiState=6ae2d81bf7dd7a478c9b1770)
- Anyone can open, inspect, measure, or create a copy/branch directly in their browser without installing CAD software.
