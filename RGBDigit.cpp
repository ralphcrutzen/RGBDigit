/*
  RGBDigit.cpp - Library for controlling an RGBDigit from http://rgbdigit.com/
  Created by Ralph Crützen, September 2015.
  Released into the public domain.
*/

#include "RGBDigit.h"

RGBDigit::RGBDigit(int nDigits)
  : Adafruit_NeoPixel(8 * nDigits, 12, NEO_GRB + NEO_KHZ800),
  _nDigits(nDigits), _irRecv(10)
{
  _rArray = new byte[8 * nDigits]; // to store red values of each LED
  _gArray = new byte[8 * nDigits]; // to store green values of each LED
  _bArray = new byte[8 * nDigits]; // to store blue values of each LED

  //_irRecv = new IRrecv(10);
  //_irResults = new decode_results;
}

RGBDigit::~RGBDigit()
{
  //delete _irRecv;
  //delete _irResults;
  delete [] _rArray;
  delete [] _gArray;
  delete [] _bArray;
}

void RGBDigit::begin()
{
  Wire.begin();

  // init IR reveiver
  _irRecv.enableIRIn();

  //init RTC
  setSyncProvider(RTC.get);

  // init led strip
  Adafruit_NeoPixel::begin();
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
    if (_characterArray[segm%8][character]) {
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

unsigned long RGBDigit::readIR()
{
  if (_irRecv.decode(&_irResults)) {
    delay(250);
    _irRecv.resume();
    return _irResults.value;
  }
  else
    return irNone;
}
