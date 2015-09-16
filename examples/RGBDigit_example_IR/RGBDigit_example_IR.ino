/*  RGBDigit infrared remote example sketch
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

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel
#include <IRremote.h> //http://z3t0.github.io/Arduino-IRremote/
#include <DS3232RTC.h> //http://github.com/JChristensen/DS3232RTC
#include <Time.h> //https://github.com/PaulStoffregen/Time
#include <RGBDigit.h>

// If necessary, change the number of digits in the next line
#define nDigits 4
RGBDigit rgbDigit(nDigits);       // uses default pin 12
//RGBDigit rgbDigit(nDigits, 6);  // uses another pin; 6 in this example

unsigned long button;

void setup() {
  Serial.begin(9600);
  rgbDigit.begin();
  rgbDigit.clearAll();
  // If necessary, set the time of the RTC (h, m, s, d, m, y)
  // rgbDigit.setTimeDate(20, 43, 0, 15, 9, 15);

  int h = rgbDigit.getHour();
  int h1 = h/10;                      // left digit
  int h2 = h - (h/10)*10;             // right digit
  rgbDigit.setDigit(h1, 0, 64, 0, 0); // show on digit 0 (=1st). Color is rgb(64,0,0).
  rgbDigit.setDigit(h2, 1, 64, 0, 0); // show on digit 1 (=2nd). Color is rgb(64,0,0).
  int m = rgbDigit.getMinute();
  int m1 = m/10;
  int m2 = m - (m/10)*10;
  rgbDigit.setDigit(m1, 2, 64, 0, 0); // show on digit 2 (=3rd). Color is rgb(64,0,0).
  rgbDigit.setDigit(m2, 3, 64, 0, 0); // show on digit 3 (=4th). Color is rgb(64,0,0).
  rgbDigit.showDot(1, 64, 64, 64);    // show dot on digit 1 (=2nd). Color is rgb(64,64,64).
}

void loop() {
  button = rgbDigit.readIR();
  if (button != RGBDigit::irNone) {
    byte b = rgbDigit.getBrightness();
    b = (b + 16) % 256;
    rgbDigit.setBrightness(b);
  }
  switch (button) {
    case RGBDigit::irPower:
      Serial.println("Power");
      rgbDigit.setColor(64, 64, 64);
      break;
    case RGBDigit::irA:
      Serial.println("A");
      rgbDigit.setColor(64, 0, 0);
      break;
    case RGBDigit::irB:
      Serial.println("B");
      rgbDigit.setColor(0, 64, 0);
      break;
    case RGBDigit::irC:
      Serial.println("C");
      rgbDigit.setColor(0, 0, 64);
      break;
    case RGBDigit::irUp:
      Serial.println("Up");
      rgbDigit.setColor(64, 64, 0);
      break;
    case RGBDigit::irDown:
      Serial.println("Down");
      rgbDigit.setColor(64, 0, 64);
      break;
    case RGBDigit::irLeft:
      Serial.println("Left");
      rgbDigit.setColor(0, 64, 64);
      break;
    case RGBDigit::irRight:
      Serial.println("Right");
      rgbDigit.setColor(0, 64, 16);
      break;
    case RGBDigit::irSelect:
      Serial.println("Select");
      rgbDigit.setColor(64, 16, 0);
      break;
    case RGBDigit::irNone:
      break;
    default:
      Serial.println("Unknown; stop fiddling :-)");
      break;
  }
}

