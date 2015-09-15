/*
  RGBDigit.h - Library for controlling an RGBDigit from http://rgbdigit.com/
  Created by Ralph Crützen, September 2015.
  Released into the public domain.
*/

#ifndef RGBDigit_h
#define RGBDigit_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel
#include <IRremote.h> //http://z3t0.github.io/Arduino-IRremote/
#include <DS3232RTC.h> //http://github.com/JChristensen/DS3232RTC
#include <Time.h> //https://github.com/PaulStoffregen/Time

class RGBDigit : public Adafruit_NeoPixel {
  public:
    RGBDigit(int nDigits);
    ~RGBDigit();
    void begin();
    void clearAll();
    void setDigit(int character, int digit, byte red, byte green, byte blue);
    void clearDigit(int digit);
    void showDot(int digit, byte red, byte green, byte blue);
    void clearDot(int digit);
    void segmentOn(int digit, byte segment, byte red, byte green, byte blue);
    void segmentOff(int digit, byte segment);
    bool isSegmentOn(int digit, byte segment);
    void setColor(byte red, byte green, byte blue);
    void setColor(int digit, byte red, byte green, byte blue);
    void setTimeDate(int hour, int minute, int second, int day, int month, int year);
    int getHour();
    int getMinute();
    int getSecond();
    int getDay();
    int getMonth();
    int getYear();
    unsigned long readIR();
    void resumeIR();
    static const unsigned long irPower = 0x10EFD827;
    static const unsigned long irA = 0x10EFF807;
    static const unsigned long irB = 0x10EF7887;
    static const unsigned long irC = 0x10EF58A7;
    static const unsigned long irUp = 0x10EFA05F;
    static const unsigned long irDown = 0x10EF00FF;
    static const unsigned long irLeft = 0x10EF10EF;
    static const unsigned long irRight = 0x10EF807F;
    static const unsigned long irSelect = 0x10EF20DF;
    static const unsigned long irNone = 0;
    unsigned long button = 0;
  private:
    int _nDigits;
    IRrecv _irRecv;
    decode_results _irResults;
    const bool _characterArray [8][13] =
      {//0  1  2  3  4  5  6  7  8  9  c  - off
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0}, //a             a
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0}, //b          f     b
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, //c             g
        {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0}, //d          e     c
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}, //e             d
        {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0}, //f
        {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0}, //g
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //h
      };
      byte* _rArray;
      byte* _gArray;
      byte* _bArray;
};

#endif
