/*  RGBDigit temperature example sketch
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

float temp;
byte hue = 0;
byte tempPos = 1;

void setup() {
  Serial.begin(9600);
  rgbDigit.begin();
  rgbDigit.clearAll();
}

void loop() {
  temp = rgbDigit.readTemp();
  Serial.println(temp);
  showTemp(temp);
  // showTemp(-12.34); // test a negative temperature without having to put your rgbDigit in a freezer :-)
  delay(2000);
}

void showTemp(float temp) {
  byte red = 0, green = 0, blue = 0;
  int hue = temp;
  int t = abs(temp*100);
  int digit1 = t/1000;
  int digit2 = (t - 1000*digit1)/100;
  int digit3 = (t - 1000*digit1 - 100*digit2)/10;
  if (temp >= 0) {
    if (hue > 75) {
      red = 255;
      green = 0;
    }
    else {
      red = hue*3;
      green = 255 - red;
    }
    rgbDigit.setDigit(digit1, 0, red, green, blue);
    rgbDigit.setDigit(digit2, 1, red, green, blue);
    rgbDigit.setDigit(digit3, 2, red, green, blue);
    rgbDigit.showDot(1, red, green, blue);
  }
  else { // temp < 0
    blue = hue*5;
    green = 255 - blue;
    rgbDigit.setDigit('-', 0, red, green, blue);
    rgbDigit.setDigit(digit1, 1, red, green, blue);
    rgbDigit.setDigit(digit2, 2, red, green, blue);
    rgbDigit.clearDot(1);
  }
  rgbDigit.setDigit('*', 3, red, green, blue); // use the '*' character for a degree sign
}

