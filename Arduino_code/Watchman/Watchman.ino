/*
File:      Watchman.ino
MCU Board: Seeed XIAO RP2040
Started:   2023-01-02
Edited:    2023-01-15
Author:    Tauno Erik

Arduino UF2 file location:
/home/taunoerik/.var/app/cc.arduino.IDE2/cache/
*/

#include <Adafruit_NeoPixel.h>

#define DEBUG
#include "utils_debug.h" // DEBUG_PRINT("Message");
#include "colors.h"      // Predefined colors

// LED directions
#define CW  0  // ClockWise
#define CCW 1  // CounterClockWise


// XIAO RP2040 on board RGB LED
const int BOARD_RGB_PIN = 12;
const int BOARD_RGB_POWER_PIN = 11;
const int PIXELS_ON_BOARD = 1;

Adafruit_NeoPixel on_board(PIXELS_ON_BOARD, BOARD_RGB_PIN, NEO_GRB + NEO_KHZ800);


// Circular RGB LED stripe
const int RGB_LED_PIN = D6;
const int RGB_LED_COUNT = 16;

Adafruit_NeoPixel strip(RGB_LED_COUNT, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// Human Radar sensor
const int RADAR_SENSOR_PIN = D4;

int colors[NUM_OF_COLORS][3] = {
  {AMBER},
  {AQUA},
  {BLUE},
  {CYAN},
  {GOLD},
  {GREEN},
  {JADE},
  {MAGENTA},
  {OLD_LACE},
  {ORANGE},
  {PINK},
  {PURPLE},
  {RED},
  {TEAL},
  {WHITE},
  {YELLOW}
};


// Core 0
void setup() {
  strip.begin();
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  pinMode(RADAR_SENSOR_PIN, INPUT);
}

void loop() {

  bool is_movment = digitalRead(RADAR_SENSOR_PIN);
  bool flag = false;

  if ( (is_movment == true) && (flag == false) ) {
    DEBUG_PRINT("Motion Detected");
    flag = true;

    //int r = random(255);
    //int g = random(255);
    //int b = random(255);

    // Sellect one of predefined colors
    int nr = random(NUM_OF_COLORS);

    wipe_color(colors[nr][0], colors[nr][1], colors[nr][2], 50);
    //fade_out(colors[nr][0], colors[nr][1], colors[nr][2]);
    delay(500);
    wipe_off(50, CCW);
  }

  if (is_movment == false) {
    DEBUG_PRINT(".");
    flag = false;
  }
  
  /*
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
  */
}


// Core 1
void setup1() {
  DEBUG_PRINT("Core 1 setup\n");
  /*
  on_board.begin();
  pinMode(BOARD_RGB_POWER_PIN, OUTPUT);
  digitalWrite(BOARD_RGB_POWER_PIN, HIGH);
  on_board.setBrightness(60);
  */
}

void loop1() {
  //Serial.printf("\nCore temperature: %2.1fC\n", analogReadTemp()); // It does not look right ?!

/*
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    on_board.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    on_board.show(); // Update strip with new contents
    delay(10);  // Pause for a moment
  }
*/
}

/*
Turn pixels OFF, clockwise
*/
void wipe_off(int wait, int dir) {
  DEBUG_PRINT("wipe_off()");

  if (dir == CW) {
    uint32_t color = strip.Color(0, 0, 0);
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
      strip.show();
      delay(wait);
    }
  }
  if (dir == CCW) {
    uint32_t color = strip.Color(0, 0, 0);
    for (int i = strip.numPixels(); i >= 0; i--) {
      strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
      strip.show();
      delay(wait);
    }

  }

}

/*
Turn pixels ON, clockwise
*/
void wipe_color(int r, int g, int b, int wait) {
  uint32_t color = strip.Color(r, g, b);

  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);
  }
}

/*
*/
void fade_out(int r, int g, int b) {
  uint32_t color = strip.Color(r, g, b);

  for (int i=100; i>0; --i) {
  strip.setBrightness(i);
  strip.show();
  delay(10);
  }
  
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}