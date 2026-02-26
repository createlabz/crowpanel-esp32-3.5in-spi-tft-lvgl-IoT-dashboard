# 🖥 CrowPanel ESP32 3.5" SPI TFT LVGL IoT Dashboard

## ✅ This is a working Arduino project

This repository contains a **fully working LVGL 8.1.0 project** for:

- CrowPanel / Elecrow ESP32-S3
- 3.5" ILI9488 SPI TFT
- FT6236 capacitive touch
- LovyanGFX display driver
- PSRAM enabled

This project customizes the original **Elecrow `lv_demo_widgets`** and converts it into a stable IoT dashboard base template.

---

# 🎯 Project Purpose

This repo is based on the Elecrow LVGL example but:

- ✔ Cleaned and stabilized  
- ✔ Configured for LVGL 8.1.0  
- ✔ Optimized for ESP32-S3  
- ✔ Verified working touch + display  
- ✔ Ready for IoT dashboard customization  

This is intended to be a **base template** for building real LVGL dashboards.

---

# 📦 How To Install (From ZIP)

## Step 1 — Download This Repository

Download the ZIP from:

https://github.com/createlabz/crowpanel-esp32-3.5in-spi-tft-lvgl-IoT-dashboard

Click the green **Code** button, then click **Download ZIP**.

Extract it anywhere on your computer.

---

## Step 2 — Open the Arduino Project

Open the file:

LVGL_SPI_.ino

using Arduino IDE.

---

# 📚 Required Libraries

You MUST install the correct versions:

| Library | Version |
|----------|----------|
| LVGL | 8.1.0 |
| LovyanGFX | 1.2.19 |
| ESP32 Arduino Core | 3.3.7 |

⚠ Do NOT mix LVGL 8.3.x with this project.

---

# 🎨 Customized `lv_demos` Library (IMPORTANT)

This project uses a customized version of `lv_demos`.

Download it from:

https://github.com/createlabz/lv_demos

---

## 🔥 VERY IMPORTANT — Install Correctly

After downloading the ZIP of `lv_demos`:

### Option 1 (Recommended)

In Arduino IDE:

Sketch → Include Library → Add .ZIP Library...

Select the downloaded ZIP file.

---

### Option 2 (Manual Install)

Extract and place the folder inside:

C:\Users\<YourUser>\Documents\Arduino\libraries\

After installation, it must appear exactly like this:

Documents  
└── Arduino  
  └── libraries  
    └── lv_demos  
      ├── src  
      ├── lv_demo_widgets  
      ├── lv_demo_music  
      └── ...

---

# 🚨 Critical Requirement

The customized `lv_demos` MUST be located inside:

Documents/Arduino/libraries/

If placed anywhere else:

- Arduino will not detect it  
- It may use another conflicting version  
- You may get errors like:
  - 'lv_demo_music' was not declared  
  - undefined reference  
  - Multiple libraries found  

---

# 🔎 Verify Installation

When compiling, Arduino should show something like:

Using library lv_demos at version 8.1.0 in folder:  
C:\Users\<YourUser>\Documents\Arduino\libraries\lv_demos

If a different path appears, remove duplicate versions.

---

# ⚙ Board Settings

In Arduino IDE:

- Board: ESP32S3 Dev Module
- Flash Size: 16MB
- PSRAM: Enabled (OPI)
- Partition Scheme: app3M_fat9M_16MB
- CPU Frequency: 240 MHz

---

# 🧠 Where To Customize UI

To modify the dashboard UI:

Open:

Documents/Arduino/libraries/lv_demos/src/lv_demo_widgets/lv_demo_widgets.c

You can freely edit:

- Layout  
- Buttons  
- Charts  
- Labels  
- Animations  
- Colors  
- Styles  
- Grid/Flex layout  
- Event handlers  

This file controls the main dashboard UI.

---

# ✅ Verified Working

| Component | Status |
|------------|--------|
| Display (ILI9488 SPI) | ✅ Working |
| Touch (FT6236 I2C) | ✅ Working |
| LVGL Core | ✅ Working |
| Widgets Demo (Customized) | ✅ Working |
| PSRAM Enabled | ✅ Working |

---

# ⚡ Performance Notes

Recommended SPI speed:

cfg.freq_write = 40000000;

60 MHz may work but depends on wiring quality.

---

# 📌 Summary

This project provides:

- A stable LVGL 8.1.0 template  
- Working CrowPanel integration  
- Clean base for IoT dashboard development  
- Proper library installation guidance  

---

If you encounter issues, check:

- Duplicate `lv_demos` libraries  
- LVGL version mismatch  
- Incorrect board settings  
- PSRAM not enabled  

---

Happy building 🚀
