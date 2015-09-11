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
#include <Time.h> //http://www.arduino.cc/playground/Code/Time

class RGBDigit : public Adafruit_NeoPixel {
  public:
    RGBDigit(int nDigits);
    ~RGBDigit();
    void clearAll();
    void digitOn(int character, int digit, byte red, byte green, byte blue);
    void digitOff(int digit);
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
  private:
    int _nDigits;
    IRrecv* _ir;
    const bool _characte_rArray [8][13] =
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
