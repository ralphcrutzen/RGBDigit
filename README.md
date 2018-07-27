This project is licensed under Creatice Commons Attribution-ShareAlike 4.0 International (https://creativecommons.org/licenses/by-sa/4.0/)

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
* Time https://github.com/PaulStoffregen/Time (for the `RGBDigit_example_display.ino` example)

Use the sketches in the Examples directory to test the library!

## Segments per digit and choice of NeoPixel type
You can ignore this section if you are working with the standard RGBDigit module.

If you have made your own RGBDigit then you can use this section to set the library up for your digit.

####Segments per digit
The standard 7-segment display has 8 segments (7 for the digit and a decimal point).  If your display has only the 7 (ie no decimal point) then you need to call the constructor specifying that there are 7 segments per digit as opposed to the default 8.

`RGBDigit rgbDigit(nDigits, 6);` in the examples becomes `RGBDigit rgbDigit(nDigits, 6, NEO_GRB + NEO_KHZ800, 7);`

####Choice of NeoPixel type
The standard RGBDigit module uses the type `` but if you've made your own this might be different.  This may cause incorrect colours to display for example.  You can set the type of NeoPixel to use in the constructor:

`RGBDigit rgbDigit(nDigits, 6);` in the examples becomes `RGBDigit rgbDigit(nDigits, 6, NEO_GRB + NEO_KHZ800);` (simply use the appropriate definition from the documentation of the Arduino_NeoPixel library.  If the option is omitted it defaults to `NEO_GRB + NEO_KHZ800`.

## Class methods
Note that for all *digit* parameters, the first digit has index 0, the second digit has index 1, etc.

Where `segmentsPerDigit` is not specified in the constructor call, or is set to `8`; the *segment* parameters can be values from 0 to 7, every number corresponding to the following positions:

       0
    5     1
       6
    4     2
       3      7

Where `segmentsPerDigit` is set to `7` the *segment* parameters can be values from 0 to 6 (no decimal point) and correspond to the following positions:

       0
    5     1
       6
    4     2
       3

#####```RGBDigit(int nDigits, int pin = 12, neoPixelType t=NEO_GRB + NEO_KHZ800, int segmentsPerDigit = 8);```

The constructor of the RGBDigit class. *nDigits* is the number of digits. *pin* is the pin number, which defaults to pin 12 if this parameter is omitted.  Provision is made to change the type of NeoPixel using the types defined in the Adafruit_NeoPixel library.  This defaults to `NEO_GRB + NEO_KHZ800` the type used in the RGBDigit.  Further more the option is given to set the number of segments per digit to 7 or 8 depending on whether a decimal point is present on the display (see above for details).

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

Show dot on *digit* in color rgb(*red*,*green*,*blue*). This does nothing when `segmentsPerDigit` is set to `7`.

#####```void clearDot(int digit);```

Clear dot on *digit*. This does nothing when `segmentsPerDigit` is set to `7`.

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
