# RGBDigit
Arduino library for http://rgbdigit.com/

The purpose of this library is to provide a *simple* and *intuitive* interface to programming an RGBDigit.

Note that it is a work in progress. Not all functionality (like the infrared remote or reading temerature values) is covered yet.

Because I only own a RGBDigit shield without a temparature sensor, I'm not planning to add temperature functions to the library (for now...)

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

###```void clearAll();```

Clear all digits.

###```void setDigit(int character, int digit, byte red, byte green, byte blue);```

Show *character* on *digit* in color rgb(*red*,*green*,*blue*).

###```void clearDigit(int digit);```

Clear *digit*.

###```void showDot(int digit, byte red, byte green, byte blue);```

Show dot on *digit* in color rgb(*red*,*green*,*blue*). 

###```void clearDot(int digit);```

Clear dot on *digit*. .

###```void segmentOn(int digit, byte segment, byte red, byte green, byte blue);```

Show *segment* on *digit* in color rgb(*red*,*green*,*blue*). 

###```void segmentOff(int digit, byte segment);```

Clear *segment* on *digit*.

###```bool isSegmentOn(int digit, byte segment);```

Returns True if *segment* on *digit* is on. Otherwise, returns False.

###```void setColor(byte red, byte green, byte blue);```

Set the color of all digits to color rgb(*red*,*green*,*blue*).

###```void setColor(int digit, byte red, byte green, byte blue);```

Set the color of *digit* to color rgb(*red*,*green*,*blue*).

###```void setTimeDate(int hour, int minute, int second, int day, int month, int year);```

Set the time and date.

###```int getHour();

###int getMinute();

###int getSecond();

###int getDay();

###int getMonth();

###int getYear();```

Hopefully speak for themselves...

## To do:
* Add infrared remote functionality
* Add alarm functionality
* ...
