/*  RGBDigit class implementation
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

#include "RGBDigit.h"

RGBDigit::RGBDigit(int nDigits, int pin)
  : Adafruit_NeoPixel(8 * nDigits, pin, NEO_GRB + NEO_KHZ800),
  _brightness(32), _nDigits(nDigits)
{
  _rArray = new byte[8 * nDigits]; // to store red values of each LED
  _gArray = new byte[8 * nDigits]; // to store green values of each LED
  _bArray = new byte[8 * nDigits]; // to store blue values of each LED
}

RGBDigit::~RGBDigit()
{
  delete [] _rArray;
  delete [] _gArray;
  delete [] _bArray;
}

void RGBDigit::begin()
{
  Wire.begin();

  // init led strip
  Adafruit_NeoPixel::begin();
  Adafruit_NeoPixel::setBrightness(_brightness);
}

void RGBDigit::clearAll()
{
  for (int segm = 0; segm < 8*_nDigits; segm++) {
    _rArray[segm] = 0;
    _gArray[segm] = 0;
    _bArray[segm] = 0;
    setPixelColor(segm, 0, 0, 0);
  }
  show();
}

void RGBDigit::setDigit(int number, int digit, byte red, byte green, byte blue)
{
  if (number < 0 || number > 9) return;
  for (int segm = 8*digit; segm < 8*digit + 8; segm++) {
    if (_numberArray[segm % 8][number]) {
      _rArray[segm] = red;
      _gArray[segm] = green;
      _bArray[segm] = blue;
    }
    else {
      _rArray[segm] = 0;
      _gArray[segm] = 0;
      _bArray[segm] = 0;
    }
    setPixelColor(segm, _rArray[segm], _gArray[segm],  _bArray[segm]);
  }
  show();
}


void RGBDigit::setDigit(char character, int digit, byte red, byte green, byte blue)
{
  // First, handle special characters
  if (character == ' ') {
    clearDigit(digit);
    return;
  }
  if (character == '.') {
    showSpecialCharacter(0, digit, red, green, blue);
    return;
  }
  if (character == '-') {
    showSpecialCharacter(1, digit, red, green, blue);
    return;
  }
  if (character == '_') {
    showSpecialCharacter(2, digit, red, green, blue);
    return;
  }
  if (character == '(' || character == '[' || character == '{') {
    showSpecialCharacter(3, digit, red, green, blue);
    return;
  }
  if (character == ')' || character == ']' || character == '}') {
    showSpecialCharacter(4, digit, red, green, blue);
    return;
  }
  if (character == '*') {
    showSpecialCharacter(5, digit, red, green, blue);
    return;
  }

  // Numbers
  if (character >= 48 && character <= 57) {
    int number = character - 48;
    setDigit(number, digit, red, green, blue);
    show();
    return;
  }

  // Check if character isn't letter from alphabet
  if (character < 'A' || (character > 'Z' && character < 'a') || character > 'z')
    return;

  // Decapitalize
  if (character <= 'Z')
    character = character + 32;

  for (int segm = 8*digit; segm < 8*digit + 8; segm++) {
    if (_characterArray[segm % 8][character - 97]) {
      _rArray[segm] = red;
      _gArray[segm] = green;
      _bArray[segm] = blue;
    }
    else {
      _rArray[segm] = 0;
      _gArray[segm] = 0;
      _bArray[segm] = 0;
    }
    setPixelColor(segm, _rArray[segm], _gArray[segm],  _bArray[segm]);
    }
    show();
}

void RGBDigit::showSpecialCharacter(byte index, int digit, byte red, byte green, byte blue) {
  for (int segm = 8*digit; segm < 8*digit + 8; segm++) {
    if (_symbolArray[segm % 8][index]) {
      _rArray[segm] = red;
      _gArray[segm] = green;
      _bArray[segm] = blue;
    }
    else {
      _rArray[segm] = 0;
      _gArray[segm] = 0;
      _bArray[segm] = 0;
    }
    setPixelColor(segm, _rArray[segm], _gArray[segm],  _bArray[segm]);
    show();
  }
}

void RGBDigit::clearDigit(int digit)
{
  for (int segm = 8*digit; segm < 8*digit + 8; segm++) {
    _rArray[segm] = 0;
    _gArray[segm] = 0;
    _bArray[segm] = 0;
    setPixelColor(segm, 0, 0, 0);
  }
  show();
}

void RGBDigit::showDot(int digit, byte red, byte green, byte blue)
{
  setPixelColor(8*digit + 7, red, green, blue);
  show();
}

void RGBDigit::clearDot(int digit)
{
  setPixelColor(8*digit + 7, 0, 0, 0);
  show();
}

void RGBDigit::segmentOn(int digit, byte segment, byte red, byte green, byte blue)
{
  int segm = 8*digit + segment;
  _rArray[segm] = red;
  _gArray[segm] = green;
  _bArray[segm] = blue;
  setPixelColor(segm, red, green, blue);
  show();
}

void RGBDigit::segmentOff(int digit, byte segment)
{
  int segm = 8*digit + segment;
  _rArray[segm] = 0;
  _gArray[segm] = 0;
  _bArray[segm] = 0;
  setPixelColor(segm, 0, 0, 0);
  show();
}

bool RGBDigit::isSegmentOn(int digit, byte segment)
{
  int segm = 8*digit + segment;
  return (_rArray[segm] > 0) || (_gArray[segm] > 0) || (_bArray[segm] > 0);
}

void RGBDigit::setColor(byte red, byte green, byte blue)
{
  for (int segm = 0; segm < 8*_nDigits; segm++) {
    if ((segm - 7) % 8 != 0) { // exclude dots
      if ((_rArray[segm] != 0) || (_gArray[segm] != 0) || (_bArray[segm] != 0)) {
        _rArray[segm] = red;
        _gArray[segm] = green;
        _bArray[segm] = blue;
        setPixelColor(segm, _rArray[segm], _gArray[segm],  _bArray[segm]);
      }
    }
  }
  show();
}

void RGBDigit::setColor(int digit, byte red, byte green, byte blue)
{
  for (int segm = 8*digit; segm < 8*digit + 7; segm++) {
    if ((_rArray[segm] != 0) || (_gArray[segm] != 0) || (_bArray[segm] != 0)) {
      _rArray[segm] = red;
      _gArray[segm] = green;
      _bArray[segm] = blue;
      setPixelColor(segm, _rArray[segm], _gArray[segm],  _bArray[segm]);
    }
  }
  show();
}

void RGBDigit::setBrightness(byte brightness){
  _brightness = brightness;
  Adafruit_NeoPixel::setBrightness(brightness);
}

byte RGBDigit::getBrightness() {
  return _brightness;
}

