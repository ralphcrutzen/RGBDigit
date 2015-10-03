# RGBDigit
Arduino library for http://rgbdigit.com/

The purpose of this library is to provide a *simple* and *intuitive* interface to programming an RGBDigit.

Note that it is a work in progress. Not all functionality (like reading temerature values) is covered yet.

## Installation instructions
* Download the zip file
* Extract it to your Arduino library folder
* Rename the RGBDigit-master folder to RGBDigit
 
You also have to download and install the following libraries:
* Adafruit NeoPixel https://github.com/adafruit/Adafruit_NeoPixel
* IRremote http://z3t0.github.io/Arduino-IRremote/
* DS3232RTC http://github.com/JChristensen/DS3232RTC
* Time http://www.arduino.cc/playground/Code/Time

Use the sketch in the Examples directory to test the library!

## Class methods
Note that for all *digit* parameters, the first digit has index 0, the second digit has index 1, etc.

The *segment* parameters can be values from 0 to 7, every number corresponding to the following position:

       0
    5     1
       6
    4     2
       3      7

#####```RGBDigit(int nDigits, int pin = 12);```

The consttructor of the RGBDigit class. *nDigits* is the number of digits. *pin* is the pin number, which defaults to pin 12 if this parameter is omitted.

#####```void begin();```

Initialises the RGBDigit.

#####```void clearAll();```

Clear all digits.

#####```void setDigit(int number, int digit, byte red, byte green, byte blue);```

Show *number* (from 0 - 9) on *digit* in color rgb(*red*,*green*,*blue*).

#####```void setDigit(char character, int digit, byte red, byte green, byte blue);```

Show *character* on *digit* in color rgb(*red*,*green*,*blue*). Valid characters are letters (case insensitive) from *a* to *z*, the dot (*.*), dash (*-*), underscore (*_*), brackets ( *( ) { } [ ]* ) and space . Use an asterisk (*) for the degree sign.

#####```void clearDigit(int digit);```

Clear *digit*.

#####```void showDot(int digit, byte red, byte green, byte blue);```

Show dot on *digit* in color rgb(*red*,*green*,*blue*). 

#####```void clearDot(int digit);```

Clear dot on *digit*. .

#####```void segmentOn(int digit, byte segment, byte red, byte green, byte blue);```

Show *segment* on *digit* in color rgb(*red*,*green*,*blue*). 

#####```void segmentOff(int digit, byte segment);```

Clear *segment* on *digit*.

#####```bool isSegmentOn(int digit, byte segment);```

Returns True if *segment* on *digit* is on. Otherwise, returns False.

#####```void setColor(byte red, byte green, byte blue);```

Set the color of all digits to color rgb(*red*,*green*,*blue*).

#####```void setColor(int digit, byte red, byte green, byte blue);```

Set the color of *digit* to color rgb(*red*,*green*,*blue*).

#####```void setBrightness(byte brightness);```

Set the *brightness* of the strip to a value from 0 to 255.

#####```byte getBrightness();```

Returns the brightness of the strip.

#####```void setTimeDate(int hour, int minute, int second, int day, int month, int year);```

Set the time and date.

#####```int getHour();```

#####```int getMinute();```

#####```int getSecond();```

#####```int getDay();```

#####```int getMonth();```

#####```int getYear();```

Returns the different time values.

#####```unsigned long readIR();```

Returns one of the following (static) values if the button of the remote is pressed, or ```RGBDigit::irNone``` if no button is pressed.

    RGBDigit::irPower
    RGBDigit::irA
    RGBDigit::irB
    RGBDigit::irC
    RGBDigit::irUp
    RGBDigit::irDown
    RGBDigit::irLeft
    RGBDigit::irRight
    RGBDigit::irSelect

#####```float readTemp();```

Returns the temperature in degrees Celcius.
