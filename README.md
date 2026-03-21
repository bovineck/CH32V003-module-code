# CH32V003 Organic Starfield & Reactive VU Meter

An advanced lighting controller for the ultra-low-cost WCH CH32V003 RISC-V microcontroller. This project moves beyond simple "on/off" blinking to create organic, fluid lighting effects using software PWM and digital signal filtering.

## 🌟 Features

* **Organic Twinkle Engine:** Uses randomized peak brightness, pulse speed, and timing to simulate a natural starfield.
* **Software PWM Fading:** Implements smooth 8-bit fading on pins without native hardware PWM support.
* **Dampened VU Meter:** A voice-reactive mode using an **Exponential Moving Average (EMA)** filter to transform a standard microphone module into a smooth, professional-grade volume meter.
* **Memory Optimized:** Hand-tuned integer math to stay under the 16KB Flash limit, avoiding heavy floating-point library bloat.

## 🛠 Hardware & Resources

* **MCU:** WCH CH32V003 (RISC-V @ 24MHz, 16KB Flash, 2KB RAM).
* **Core:** [OpenWCH Arduino CH32](https://github.com/openwch/arduino-wch32v003)
* **Datasheet:** [WCH CH32V003 Official Datasheet (PDF)](https://www.wch-ic.com/downloads/CH32V003DS0_PDF.html)
* **Input:** Analog Microphone Module (connected to Pin A4 / PA4).
* **Output:** 8x LEDs connected to the defined `LedArray`.

## 📋 Pin Mapping (Logical to Physical)

| Function | Arduino Pin | MCU Port/Pin |
| :--- | :--- | :--- |
| LED Array | PA1, PA2, PC0, PC1, PC2, PC3, PC4, PD4 | PA1, PA2, PC0, PC1, PC2, PC3, PC4, PD4 |
| Mic Input | A4 | PA4 |

## 🚀 Technical Note: Fixed-Point Smoothing

To save over 4KB of Flash memory, this project avoids `float` math. The voice smoothing is calculated using integer-based weighted averages:
`dampenedVolume = ((dampenedVolume * 93) + (rawReading * 7)) / 100;`

## About OneCircuit
Created by OneCircuit and Gemini for the maker community. This project focuses on professional-grade code for hobbyist hardware.

* **YouTube:** [OneCircuit YouTube Channel](https://www.youtube.com/@onecircuit-as)
* **Blog:** [OneCircuit Blog](https://onecircuit.blogspot.com/)
* **GitHub:** [OneCircuit Repositories](https://github.com/bovineck/)

---

## ⚖️ License

This project is licensed under the **MIT License**. 

*Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files...* (See the LICENSE file for full details).

---

