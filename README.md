# RGBDigit
Arduino library for http://rgbdigit.com/

## Installation instructions
* Download the zip file
* Extract it to your Arduino library folder
* Rename the RGBDigit-Master folder to RGBDigit
 
You also have to download and install the following libraries:
* Adafruit NeoPixel https://github.com/adafruit/Adafruit_NeoPixel
* IRremote http://z3t0.github.io/Arduino-IRremote/
* DS3232RTC http://github.com/JChristensen/DS3232RTC
* Time http://www.arduino.cc/playground/Code/Time

## Class methods
    void clearAll();
Clear all digits.

    void setDigit(int character, int digit, byte red, byte green, byte blue);
Show number "character" on digit "digit" in color rgb(red,green,blue). Note that the first digit has index 0, the second digit has index 1, etc.

    void clearDigit(int digit);
Clear digit "digit".

    void showDot(int digit, byte red, byte green, byte blue);
Show dot on digit "digit" in color rgb(red,green,blue).

    void clearDot(int digit);
Clear dot on digit "digit".

    void segmentOn(int digit, byte segment, byte red, byte green, byte blue);
Show segment "segment" (see below) on digit "digit" in color rgb(red,green,blue).

       0
    5     1
       6
    4     2
       3

    void segmentOff(int digit, byte segment);
Clear segment "segment" on digit "digit".

    bool isSegmentOn(int digit, byte segment);
Returns True if segment "segment" on digit "digit" is on.
Otherwise, returns False.

    void setColor(byte red, byte green, byte blue);
Set the color of all digits to rgb(red,green,blue).

    void setColor(int digit, byte red, byte green, byte blue);
Set the color of digit "digit" to rgb(red,green,blue).

    void setTimeDate(int hour, int minute, int second, int day, int month, int year);
Set the time and date.

    int getHour();
    int getMinute();
    int getSecond();
    int getDay();
    int getMonth();
    int getYear();

## To do:
* Add infrared remote functionality
* Add alarm functionality
