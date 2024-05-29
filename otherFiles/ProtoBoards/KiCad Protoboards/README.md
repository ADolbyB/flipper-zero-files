# Flipperzero prototyping boards

Here is the repo with KiCAD projects with prototyping PCB for Flipper Zero.

---

**It was designed after lockup of Flipper Zero GPIO pinout, so has actual compatibility, but not supported officially for now.**

**Please use official [external module guidelines](https://docs.flipperzero.one/ru/development/ext-modules) for new developments.**

**Unofficial KiCAD FlipperZero component can be found [here](https://bitbucket.org/lomalkin/lomalkin_kicad_libs/src/master/lomalkin_kicad_footprints.pretty/FlipperZero.kicad_mod).**

---

## Flipper-protoboard

**Not recommended for production as is.**

![flipper-pb](flipper-pb/flipper-pb.png?raw=true)

* FlipperZero conenector (horizontal PLS 2.54)
* Capacitors (Tantalum type C, 0603) on both 3.3 and 5V power lines
* SWD socket (ST-discovery style, without reset line)
* 8 LEDs on GPIO pins (can be powered from 5V or 3.3V lines or switched-off)
* UART connector (with adjustable power 5V/3.3V)
* Four grounded mounting holes (M3, d3.2mm)
* Free space filled with 2.54mm pitch thru-hole pads (d0.9 mm)

## Flipper-zen

![flipper-zen](flipper-zen/flipper-zen.png?raw=true)

* FlipperZero connector (horizontal PLS 2.54) and more space for prototyping.



