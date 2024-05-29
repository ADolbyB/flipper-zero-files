#pragma once

#ifndef Buffer_h
#define Buffer_h

#include "Arduino.h"
#include "FS.h"
#include "settings.h"
//#include "SD_MMC.h"

#define BUF_SIZE 3 * 1024 // Had to reduce buffer size to save RAM. GG @spacehuhn
#define SNAP_LEN 2324 // max len of each recieved packet

//extern bool useSD;

extern Settings settings_obj;

class Buffer {
  public:
    Buffer();
    void createPcapFile(fs::FS* fs, String fn = "", bool log = false);
    void open(bool log = false);
    void close(fs::FS* fs);
    void addPacket(uint8_t* buf, uint32_t len, bool log = false);
    void save(fs::FS* fs);
    void forceSave(fs::FS* fs);
    void forceSaveSerial();
  private:
    void write(int32_t n);
    void write(uint32_t n);
    void write(uint16_t n);
    void write(uint8_t* buf, uint32_t len);

    uint8_t* bufA;
    uint8_t* bufB;

    uint32_t bufSizeA = 0;
    uint32_t bufSizeB = 0;

    bool writing = false; // acceppting writes to buffer
    bool useA = true; // writing to bufA or bufB
    bool saving = false; // currently saving onto the SD card

    String fileName = "/0.pcap";
    File file;
};

#endif
