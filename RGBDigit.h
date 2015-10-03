/*  RGBDigit class header file
    Copyright (C) 2015 Ralph Crützen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
    RGBDigit(int nDigits, int pin = 12);
    ~RGBDigit();
    void begin();
    void clearAll();
    void setDigit(int number, int digit, byte red, byte green, byte blue);
    void setDigit(char character, int digit, byte red, byte green, byte blue);
    void clearDigit(int digit);
    void showDot(int digit, byte red, byte green, byte blue);
    void clearDot(int digit);
    void segmentOn(int digit, byte segment, byte red, byte green, byte blue);
    void segmentOff(int digit, byte segment);
    bool isSegmentOn(int digit, byte segment);
    void setColor(byte red, byte green, byte blue);
    void setColor(int digit, byte red, byte green, byte blue);
    void setBrightness(byte brightness);
    byte getBrightness();
    void setTimeDate(int hour, int minute, int second, int day, int month, int year);
    int getHour();
    int getMinute();
    int getSecond();
    int getDay();
    int getMonth();
    int getYear();
    unsigned long readIR();
    float readTemp();
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
    byte _brightness;
    int _nDigits;
    IRrecv _irRecv;
    decode_results _irResults;
    const bool _numberArray [8][10] = {
    // 0  1  2  3  4  5  6  7  8  9
      {1, 0, 1, 1, 0, 1, 1, 1, 1, 1}, //a             a
      {1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, //b          f     b
      {1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, //c             g
      {1, 0, 1, 1, 0, 1, 1, 0, 1, 1}, //d          e     c
      {1, 0, 1, 0, 0, 0, 1, 0, 1, 0}, //e             d     h
      {1, 0, 0, 0, 1, 1, 1, 0, 1, 1}, //f
      {0, 0, 1, 1, 1, 1, 1, 0, 1, 1}, //g
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //h
    };
    const bool _characterArray [8][26] = {
    // a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
      {1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1},
      {1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
      {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1},
      {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
      {1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0},
      {1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}
    };
    const bool _symbolArray [8][6] = {
    // 0  1  2  3  4  5
    // .  -  _  (  )  *(deg)
      {0, 0, 0, 1, 1, 1},
      {0, 0, 0, 0, 1, 1},
      {0, 0, 0, 0, 1, 0},
      {0, 0, 1, 1, 1, 0},
      {0, 0, 0, 1, 0, 0},
      {0, 0, 0, 1, 0, 1},
      {0, 1, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0}
    };
    byte* _rArray;
    byte* _gArray;
    byte* _bArray;
    void showSpecialCharacter(byte index, int digit, byte red, byte green, byte blue);
};

#endif
