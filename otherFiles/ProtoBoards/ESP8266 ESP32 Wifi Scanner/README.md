# (WIP)

### Supports FlipperZero's Dev Board v.1

# FlipperZero WiFi Scanner Module
 WiFi Scanner Module for FlipperZero based on ESP8266/ESP32 (results with ESP8266 much better than with ESP32)
 
 This module will help you in finding specific access point physical location.  
 
 [Work demonstration](https://www.youtube.com/watch?v=ugo5sCHWutE)
 
 [![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/ugo5sCHWutE/0.jpg)](https://www.youtube.com/watch?v=ugo5sCHWutE)
 
 Proto WiFi scanner module
 
 <img src="https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module-ESP8266/blob/main/rep_images/flipper_module_proto_1.jpg?raw=true" data-canonical-src="https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module-ESP8266/blob/main/rep_images/flipper_module_proto_1.jpg?raw=true" width="450" />
 
 # Controls
 On scan page: 
  * UP - move list up by one
  * DOWN - move list down by one
  * OK (short press) - enter monitor mode
  * OK (long press) - scan again
  * BACK - exit app
  
 In monitor mode:
  * OK (long press) - scan again
  * BACK (short press) - return to scan page and scan again
  * BACK (long press) - exit app
 
 # Help project
 Feel free to contact me with your proposals and improvements to this projects.
 
 Fork and improve!
 
 Donate if you want to support author ![ua](https://icons.iconarchive.com/icons/wikipedia/flags/16/UA-Ukraine-Flag-icon.png)
 
 **[SUPPORT](https://github.com/SequoiaSan/SequoiaSan/blob/main/README.md)**
 
 # What do you need

 1. Wemos D1 Mini (or Mini Pro) or analog
 2. FlipperZero

# How to

## FlipperZero's Dev Board v.1
Flash firmware for Dev Board and firmware for FlipperZero from [latest release](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module/releases) 

[How To Flash .bin to ESP](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32)

[How To Update FlipperZero firmware](https://www.youtube.com/watch?v=PUn7XJrslQ4) (choose **Install from file**)


## DIY Module
Precompiled .bin for ESP and firmware for FlipperZero can be found in [latest release](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module/releases)

### [Flash ESP in you web browser](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/)

or

[How To Flash .bin to ESP](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32)


[How To Update FlipperZero firmware](https://www.youtube.com/watch?v=PUn7XJrslQ4) (choose **Install from file**)


### Or compile firmwares on your own

Compile and flash [firmware](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module-ESP8266/tree/main/FlipperZero-WiFi-Scanner_Module) on Wemos D1 Mini

Install EPS8266 board version 2.7.4 for Arduino IDE. I had issues with higher versions.

Compile firmware for FlipperZero with new [application](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module-ESP8266/tree/main/applications/wifi_scanner)

Use next schematics to solder the WiFi Scanner board for FlipperZero

![image](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module-ESP8266/blob/main/rep_images/Schematics_1.jpg?raw=true)

# How to add new application on FlipperZero

1. Copy [folders](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module-ESP8266/tree/main/FlipperZero-WiFi-Scanner-App) and paste directly into [root folder of original firmware](https://github.com/flipperdevices/flipperzero-firmware).
2. Add new applications category in [/fbt_options.py](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/fbt_options.py) my_apps for example
<pre>
FIRMWARE_APPS = {
    "default": (
        "crypto_start",
        # Svc
        "basic_services",
        # Apps
        "basic_apps",
        "updater_app",
        "archive",
        
        <b># My Apps</b>
        <b>"my_apps",</b>
        
        # Settings
        "passport",
        "system_settings",
        "about",
        # Plugins
        "basic_plugins",
        # Debug
        "debug_apps",
    ),
    "unit_tests": (
        "basic_services",
        "unit_tests",
    ),
}
</pre>
3. Add new apps category and our app into [applications/meta/application.fam](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/applications/meta/application.fam)
```
App(
    appid="my_apps",
    name="My applications for main menu",
    apptype=FlipperAppType.METAPACKAGE,
    provides=[
        "wifi_scanner",
    ],
)
```
4. Compile with any [method](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/ReadMe.md#compile-everything-1) provided by FlipperZero dev team

# Issues

I tested all the things on a test bench with Wemos D1 and all was good.
When I soldered protoboard with Wemos D1 mini pro I started to receive exceptions. It seems for some reason Wemos D1 mini doesn't run well on FlipperZero 5V.
To fast solve the issue I've added an AMS1117 voltage regulator on 5V to drop it to 3V3 and feed the module.

![image](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module-ESP8266/blob/main/rep_images/Schematics_2.jpg?raw=true)

