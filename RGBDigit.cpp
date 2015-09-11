/*
  RGBDigit.cpp - Library for controlling an RGBDigit from http://rgbdigit.com/
  Created by Ralph Crützen, September 2015.
  Released into the public domain.
*/

#include "RGBDigit.h"

#define POWER 0x10EFD827
#define P 0x10EFD827
#define A 0x10EFF807
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF


RGBDigit::RGBDigit(int nDigits)
  : Adafruit_NeoPixel(8 * nDigits, 12, NEO_GRB + NEO_KHZ800),
  _nDigits(nDigits)
{
  // init IR reveiver
  _ir = new IRrecv(10);
  _ir->enableIRIn(); // Start the receiver

  //init RTC
  setSyncProvider(RTC.get);

  _rArray = new byte[8 * nDigits]; // to store red values of each LED
  _gArray = new byte[8 * nDigits]; // to store green values of each LED
  _bArray = new byte[8 * nDigits]; // to store blue values of each LED

  // init led strip
  Adafruit_NeoPixel::begin();
}

RGBDigit::~RGBDigit()
{
  delete _ir;
  delete [] _rArray;
  delete [] _gArray;
  delete [] _bArray;
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

void RGBDigit::setDigit(int character, int digit, byte red, byte green, byte blue)
{
  for (int segm = 8*digit; segm < 8*digit + 8; segm++) {
    if (_characte_rArray[segm%8][character]) {
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
    if (_rArray[segm] != 0) _rArray[segm] = red;
    if (_gArray[segm] != 0) _gArray[segm] = green;
    if (_bArray[segm] != 0) _bArray[segm] = blue;
    setPixelColor(segm, _rArray[segm], _gArray[segm],  _bArray[segm]);
  }
  show();
}

void RGBDigit::setColor(int digit, byte red, byte green, byte blue)
{
  for (int segm = 8*digit; segm < 8*digit + 8; segm++) {
    if (_rArray[segm] != 0) _rArray[segm] = red;
    if (_gArray[segm] != 0) _gArray[segm] = green;
    if (_bArray[segm] != 0) _bArray[segm] = blue;
    setPixelColor(segm, _rArray[segm], _gArray[segm],  _bArray[segm]);
  }
  show();
}

void RGBDigit::setTimeDate(int hour, int minute, int second, int day, int month, int year)
{
  setTime(hour, minute, second, day, month, year);
  RTC.set(now());
}

int RGBDigit::getHour()
{
  return hour();
}

int RGBDigit::getMinute()
{
  return minute();
}

int RGBDigit::getSecond()
{
  return second();
}

int RGBDigit::getDay()
{
  return day();
}

int RGBDigit::getMonth()
{
  return month();
}

int RGBDigit::getYear()
{
  return year();
}
