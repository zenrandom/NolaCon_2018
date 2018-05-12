/*
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : @theDevilsVoice @p0lr_ @mzbat @dead10c5
 * Date   : March 31, 2018
 * Version: 0.4
 */

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <APA102.h>
#include <Thread.h>
#include <ThreadController.h>
#include "nola.h"
#include "MyMenu.h"

// Initialize instance of MyNetwork() class
MyMenu mymenu;

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

Thread ledThread = Thread();
Thread buttonThread = Thread();

// initialize states of things
String myText = "default"; 
int page = 1;  // page number
int inv = 1;   // which menu item to invert
int total = 5; //total menu items on page

/*
 * Check if any button was pressed
 */
void buttonCallback() {
  if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    button_press("1");
  } 
  if (digitalRead(switchPin2) == LOW) {
    button_press("2");
  } 
  if (digitalRead(switchPin3) == LOW) {
    button_press("3");
  } 
  if (digitalRead(switchPin4) == LOW) {
    button_press("4");
  }

}
void ledCallback() {
  cyberPolice();
    
 /*
  uint8_t time = millis() >> 4;
  for(uint16_t i = 0; i < ledCount; i++) {
    uint8_t p = time - i * 8;
    colors[i] = hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
  }
  ledStrip.write(colors, ledCount, brightness);
  delay(10);
 

  // send increasing white only
  if (myPattern = 1) {  
    ledStrip.startFrame();
    float power = minPower;
    for(uint16_t i = 0; i < ledCount; i++)
    {
      sendWhite(power);
      power = power * multiplier;
    }
    ledStrip.endFrame(ledCount);
  }
*/  
}

void cyberPolice() {
  myText = " CYBER\nPOLICE";
  for(uint16_t i = 0; i < ledCount; i++)
  {
    
    if (i%2 == 0) {
      //uint8_t x = time - i * 8;
      colors[i].red = 0;
      colors[i].green = 0;
      colors[i].blue = 255;
    } else {
      colors[i].red = 0;
      colors[i].green = 255;
      colors[i].blue = 0;
    }
    
  }  
  ledStrip.write(colors, ledCount, 10);
  delay(200);
  
  for(uint16_t i = 0; i < ledCount; i++)
    if (i%2 != 0) {
      //uint8_t x = time - i * 8;
      colors[i].red = 0;
      colors[i].green = 0;
      colors[i].blue = 255;
    } else {
      colors[i].red = 0;
      colors[i].green = 255;
      colors[i].blue = 0;
    }
  ledStrip.write(colors, ledCount, 5);
  delay(200);
}

int button_press(String button_num) {
  
  int my_butt = button_num.toInt();

  // UP button pressed
  if (my_butt == 1) {
    // up button pressed but already at top
    if (inv == 1) {
      return 0;
    } else {
      inv--;
    }
  }

  // DOWN button pressed
  if (my_butt == 2) {
    if (total < inv) {
      inv++;
    } else {
      // already on last menu item
      return 0;
    }
  }

  // BACK button pressed
  if (my_butt == 3) {
    
  }

  // enter button pressed
  if (my_butt == 4) {
    
  }
  
  digitalWrite(switchPin1, HIGH);  // UP
  digitalWrite(switchPin2, HIGH);  // DOWN
  digitalWrite(switchPin3, HIGH);  // BACK
  digitalWrite(switchPin4, HIGH);  // ENTER


}
void setup() {

  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0); 

  // deadlocks logo
  display.clearDisplay();
  display.drawBitmap(0, 0,  deadlocks, 128, 64, 1);
  display.display();
  delay(2000);

  // nolacon logo
  display.clearDisplay();
  display.drawBitmap(0, 0,  fdl_bmp1, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();

  // set up the buttons
  pinMode(switchPin1, INPUT_PULLUP);    // Set the switch pin as input
  digitalWrite(switchPin1, HIGH); // turn on pull up resistor
  pinMode(switchPin2, INPUT_PULLUP);
  digitalWrite(switchPin2, HIGH);
  pinMode(switchPin3, INPUT_PULLUP);
  digitalWrite(switchPin3, HIGH);
  pinMode(switchPin4, INPUT_PULLUP);
  digitalWrite(switchPin4, HIGH);
  pinMode(LED_BUILTIN, OUTPUT); // initialize the on-board LED
  digitalWrite(LED_BUILTIN, HIGH);  // turn LED off

  // Configure myThread
  ledThread.onRun(ledCallback);
  ledThread.setInterval(500);

  // Configure buttonThread
  buttonThread.onRun(buttonCallback);
  buttonThread.setInterval(250);
   
  // Adds threads to the controller
  controll.add(&ledThread);
  controll.add(&buttonThread);

}

void loop() {
  controll.run();


  
  // display page
  if (page == 1) {
    display.setCursor(0, 0);
    if (inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("bling");
      display.setTextColor(WHITE);
    } else {
      display.println("bling");
    }
    if (inv == 2) {
      display.setTextColor(BLACK, WHITE);
      display.println("network");
      display.setTextColor(WHITE);
    } else {
      display.println("network");
    }
    if (inv == 3) {
      display.setTextColor(BLACK, WHITE);
      display.println("games");
      display.setTextColor(WHITE);
    } else {
      display.println("games");
    }  
    if (inv == 4) {
      display.setTextColor(BLACK, WHITE);
      display.println("about");
      display.setTextColor(WHITE);
    } else {
      display.println("about");
    }
    if (inv == 5) {
      display.setTextColor(BLACK, WHITE);
      display.println("next");
      display.setTextColor(WHITE);
    } else {
      display.println("next");
    }
    display.println(inv);
    display.display();
  }

  if (page == 2) {
    display.setCursor(0, 0);
    if (inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("cybercop");
      display.setTextColor(WHITE);
    } else {
      display.println("cybercop");
    }
    if (inv == 2) {
      display.setTextColor(BLACK, WHITE);
      display.println("rainbow");
      display.setTextColor(WHITE);
    } else {
      display.println("rainbow");
    }
    if (inv == 3) {
      display.setTextColor(BLACK, WHITE);
      display.println("white");
      display.setTextColor(WHITE);
    } else {
      display.println("white");
    }  
    if (inv == 4) {
      display.setTextColor(BLACK, WHITE);
      display.println("about");
      display.setTextColor(WHITE);
    } else {
      display.println("about");
    }
    display.display();
  }
  

}

/* Converts a color from HSV to RGB.
 * h is hue, as a number between 0 and 360.
 * s is the saturation, as a number between 0 and 255.
 * v is the value, as a number between 0 and 255. */
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return rgb_color(r, g, b);
}


// This function sends a white color with the specified power,
// which should be between 0 and 7905.
void sendWhite(uint16_t power)
{
  // Choose the lowest possible 5-bit brightness that will work.
  uint8_t brightness5Bit = 1;
  while(brightness5Bit * 255 < power && brightness5Bit < 31)
  {
    brightness5Bit++;
  }

  // Uncomment this line to simulate an LED strip that does not
  // have the extra 5-bit brightness register.  You will notice
  // that roughly the first third of the LED strip turns off
  // because the brightness8Bit equals zero.
  //brightness = 31;

  // Set brightness8Bit to be power divided by brightness5Bit,
  // rounded to the nearest whole number.
  uint8_t brightness8Bit = (power + (brightness5Bit / 2)) / brightness5Bit;

  // Send the white color to the LED strip.  At this point,
  // brightness8Bit multiplied by brightness5Bit should be
  // approximately equal to power.
  ledStrip.sendColor(brightness8Bit, brightness8Bit, brightness8Bit, brightness5Bit);
}


