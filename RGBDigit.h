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
  private:
    byte _brightness;
    int _nDigits;
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
