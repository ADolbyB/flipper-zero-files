# WS2812B LED Tester
This application is used to test WS2812B LEDs.  You can connect the WS2812B LEDs to any available GPIO pin.  If you are powering the LEDs using the Flipper Zero, be sure to consider the power requirements of the LEDs.  The 3V3 pin has a 1200mA max current (~4 watts).  5V pin has a 1000mA max current (5 watts).

Please let me know any feedback! 
- Discord - https://discord.com/invite/NsjCvqwPAd  (@CodeAllNight)
- YouTube - https://youtube.com/@MrDerekJamison/playlists
- GitHub - https://github.com/jamisonderek/flipper-zero-tutorials
- Wiki - https://github.com/jamisonderek/flipper-zero-tutorials/wiki

# Overview
This application has three submenu items:
* Test WS2812B
* About

# Test WS2812B
- LED Pin : Select the GPIO pin that the WS2812B LED data wire is connected to.
- LED Count : select the total number of LEDs in the chain.
- LED Pattern : select the pattern to display on the LEDs.
- LED Brightness : Select the brightness of the LEDs.  The brighter the LEDs, the more power they will consume.
- Enable +5V pin : Select "Yes" if you are using pin 1 to power the LEDs (note, there is a 1000mA max current on this pin).

# About
The "About" menu item contains information about the application.

# Updates
- Version 1.9
  - Use logic LOW instead of HIGH as resting state.  Fixes first LED was "laggy" issue.
- Version 1.8
  - Renamed app to fit on Flipper Zero main menu screen
  - Improved initialization to only happen when configuring the LEDs
- Version 1.7
  - Added blanking TRESET (LOW) signal before sending data to LEDs.
  - Increased timer_buffer to uint16 to support blanking signal duration.  Maybe there is a better way to do the initial low & save memory?
  - Bug fix: Turn off remaining LEDs when reducing the number of LEDs.
- Version 1.6 
  - Added support for up to 1000 LEDs (max set in led_driver.h)
  - Added "dirty flag" to get rid of flicker when not updating the LEDs
