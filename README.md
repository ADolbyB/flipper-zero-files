# Flipper Zero Files

This is a collection of files I cleaned up and organized for use with the Flipper Zero device. I am running CFW Release FW. Files that I did not create myself were gathered from sources I have linked to here. Everything I've collected so far is in the `CFW-FW-Archive` Folder. This folder has been cleaned to get rid of non-flipper device files (like `README.md`, `*.jpg` and `*.txt` files.)

I have also included some of my own files from devices I scanned with my own FZ & their associated information in the `MyFiles` Folder.

## Flipper Repo Sources: 

 - [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero)
 - [Awesome Flipper Zero 2](https://github.com/CyberSecurityUP/awesome-flipperzero2)
 - [FzDumps](https://github.com/Z3BRO/FzDumps)
 - [All The Plugins](https://github.com/xMasterX/all-the-plugins)
 - [Unleashed Firmware](https://github.com/DarkFlippers/unleashed-firmware)
 - [Flipper](https://github.com/UberGuidoZ/Flipper)
 - [Flipper IRDB](https://github.com/UberGuidoZ/Flipper-IRDB)
 - [IR Scope App](https://github.com/kallanreed/unleashed-firmware/releases/tag/v1.0.0.0)
 - [Sub GHz Jamming](https://github.com/SHUR1K-N/Flipper-Zero-Sub-GHz-Jamming-Files)
 - [Bypass Sentry Safe](https://github.com/H4ckd4ddy/bypass-sentry-safe)
 - [FAP-list](https://github.com/playmean/fap-list)
 - [O.MG Payloads](https://github.com/hak5/omg-payloads)
 - [Flipper Zero BadUSB](https://github.com/I-Am-Jakoby/Flipper-Zero-BadUSB)

## Flipper DevBoard Sources:

 - [Black Magic Probe](https://github.com/blackmagic-debug/blackmagic) Debugger Repo.
 - [ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder) Repo.
 - [Marauder Wiki](https://github.com/justcallmekoko/ESP32Marauder/wiki/flipper-zero) For FZ WiFi Dev Board.
 - [Flipper Zero WiFi Marauder](https://github.com/0xchocolate/flipperzero-wifi-marauder) Companion App.

## Other Flipper Resources:
 
 - [Flipper Zero Dev Tutorial](https://github.com/m1ch3al/flipper-zero-dev-tutorial/tree/main) : How To develop apps for the Flipper Zero.
 - [Flipper Zero .fap Factory](https://flipc.org/build) : A cloud-based one-click tool to build Flipper Zero .fap applications from git repositories.

## Flipper Zero SD Card File Structure:

 - Source: [FlipperDevices Readme](https://github.com/flipperdevices/flipperzero-sd-card-examples/blob/dev/README.md)
 - Modifications are mine.

```
FLIPPER SD (Unleashed FW)
├── apps
├── apps_data
├── authenticator
├── badusb                          # Put Rubber Ducky scripts here
│   ├── demo_macos.txt              # MacOS sample script
│   └── demo_windows.txt            # Windows sample script
├── dolphin
│   ├── L1_Furippa1_128x64
│   │   ├── frame_x.bm              # Animation frame
│   │   └── meta.txt                # Set of rules for playing frames
│   └── manifest.txt                # Describes animation selection parameters
├── ibtnfuzzer
├── ibutton (1-Wire)
│   ├── Cyfral.ibtn                 # Cyfral key
│   ├── Dallas.ibtn                 # Dallas key
│   └── Metakom.ibtn                # Metakom key
├── infrared (IR)
│   ├── TV_bedroom.ir               # Samsung remote
│   ├── Apple_tv.ir                 # Apple tv remote
│   └── assets                      # Signal libraries
│       └── tv.ir
├── lfrfid (RFID)
│   ├── Em_marine.rfid              # EM4100 sample key 
│   ├── Hid_prox.rfid               # H10301 sample key EM4100
│   └── Indala.rfid                 # I40134 sample key
├── music_player                    # List of tunes to play
│   ├── Chasing.fmf                 # Sample tune
│   └── Marble_Machine.fmf          # Sample tune
├── nfc
│   ├── Desfire.nfc                 # Desfire card
│   ├── Ntag_213.nfc                # Ntag_213 card
│   ├── Ntag_216.nfc                # Ntag_216 card
│   ├── Classik_1k.nfc              # Classik_1k card
│   ├── RocketBank.nfc              # Banking card
│   ├── UID.nfc                     # Card with only UID data
│   └── assets                      # NFC libraries
│       ├── aid.nfc
│       ├── country_code.nfc
│       ├── currency_code.nfc
│       └── mf_classic_dict.nfc
├── picopass
├── subghz
│   ├── ****.sub                    # Captured packet
│   ├── ****_raw.sub                # Recorded raw signal
│   └── assets
│       ├── came_atomo
│       ├── keeloq_mfcodes
│       ├── keeloq_mfcodes_user
│       ├── nice_flor_s
│       ├── setting_frequency_analyzer_user
│       └── setting_user
├── subghz_remote
├── subplaylist
├── swd_scripts
├── u2f
│   ├── assets
│   │   ├── cert.der                # Public certificate
│   │   └── cert_key.u2f            # Private key
│   ├── cnt.u2f # Key counter
│   └── key.u2f # Device key
├── unirf
├── update
│   └── f7-update-dev-29042022-0eac917f
│       ├── backup.tar                                      # Flipper configuration snapshot
│       ├── flipper-z-f7-full-dev-29042022-0eac917f.dfu     # Target firmware 
│       ├── flipper-z-f7-updater-dev-29042022-0eac917f.bin  # Updater image for RAM execution
│       ├── resources.tar                                   # Assets archive
│       ├── stm32wb5x_BLE_Stack_light_fw.bin                # Radio core firmware
│       └── update.fuf                                      # Update package manifest
├── wav_player
│
├── Manifest                        # Resource files list
├── rwfiletest.bin                  # Created after running SD benchmark
└── favorites.txt                   # List of items displayed in Favorites
```

## Status:

![GitHub repo size](https://img.shields.io/github/repo-size/ADolbyB/flipper-zero-files?label=Repo%20Size&logo=github)

### DISCLAIMER:

ONLY use this repo at your own risk on your own devices, and do not violate the law with any of these apps. You should only transmit on frequencies that you are authorized to do so. In the US, refer to the FCC for radio spectrum info if you are unsure of that information. This repo is FOR EDUCATIONAL USE ONLY. If you get in trouble doing something stupid, especially jamming or causing interference, then YOU are the only one to blame. I have not been able to test everything in this repo, so USE AT YOUR OWN RISK.