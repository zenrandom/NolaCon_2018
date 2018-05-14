/*
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat @dead10c5
   Date   : March 31, 2018
   Version: 0.4
*/
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <APA102.h>
#include <Thread.h>
#include <ThreadController.h>
#include "nola.h"

// Initialize instance of MyNetwork() class
MyMenu mymenu;

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

Thread ledThread = Thread();
//Thread screenThread = Thread();
//Thread buttonThread = Thread();
//ButtonThread btn1Thread(switchPin1, 3000);
//ButtonThread btn2Thread(switchPin2, 5000);
//ButtonThread btn3Thread(switchPin3, 3000);;
//ButtonThread btn4Thread(switchPin4, 3000);;

/* Converts a color from HSV to RGB.
   h is hue, as a number between 0 and 360.
   s is the saturation, as a number between 0 and 255.
   v is the value, as a number between 0 and 255. */
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
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
  while (brightness5Bit * 255 < power && brightness5Bit < 31)
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

int button_press(String button_num) {

  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

  digitalWrite(switchPin1, HIGH);  // UP
  digitalWrite(switchPin2, HIGH);  // DOWN
  digitalWrite(switchPin3, HIGH);  // BACK
  digitalWrite(switchPin4, HIGH);  // ENTER

  int my_butt = button_num.toInt();

  // UP button pressed
  if (my_butt == 1) {
    if (mymenu.inv == 1) {
      // up button pressed but already at top
      return 0;
    } else {
      mymenu.inv -= 1;
      return 0;
    }
  }

  // DOWN button pressed
  if (my_butt == 2) {
    if (mymenu.inv < mymenu.total) {
      mymenu.inv++;
    }
    return 0;
  }

  // BACK button pressed
  if (my_butt == 3) {
    if (mymenu.page > 1 &&  mymenu.page < 6)
    {

      mymenu.page = 1;
      return 0;
    }
  }

  // enter button pressed
  if (my_butt == 4) {

    if (mymenu.page == 1 && mymenu.inv == 1) {
      // page 2 (bling)
      mymenu.page++;
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 2) {
      // page 3 (network)
      mymenu.page = 3;
      mymenu.inv = 1;
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 3) {
      // page 4 (games)
      mymenu.page = 4;
      mymenu.inv = 1;
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 4) {
      // call the about() function
      about();
      return 0;
    }

    if (mymenu.page == 2 && mymenu.inv == 1) {
      mymenu.ledpattern = 1;
      ledCallback();
      return 0;
    }
    if (mymenu.page == 2 && mymenu.inv == 2) {
      mymenu.ledpattern = 2;
      ledCallback();
      return 0;
    }
    if (mymenu.page == 2 && mymenu.inv == 3) {
      mymenu.ledpattern = 3;
      ledCallback();
      return 0;
    }

    // wireless scanner
    if (mymenu.page == 3 && mymenu.inv == 1) {

      return 0;
    }

    // burgess_pong()
    if (mymenu.page == 4 && mymenu.inv == 1) {
      burgess_pong();
      return 0;
    }

  }

}

void ledCallback() {

  if (mymenu.ledpattern == 1) {
    cyberPolice();
  }

  if (mymenu.ledpattern == 2) {
    rainbow();
  }

  // send increasing white only
  if (mymenu.ledpattern == 3) {
    ytCracker();
  }

  // turn off leds
  if (mymenu.ledpattern == 4) {
    for (uint16_t i = 0; i < ledCount; i++) {
      colors[i] = hsvToRgb(0, 0, 0);
    }
    ledStrip.write(colors, ledCount, 0);
  }
}


void cyberPolice() {
  mymenu.myText = " CYBER\nPOLICE";
  int loop = 1;

  while (loop = 1) {
    if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("1");
      yield();
      break;
    } else if (digitalRead(switchPin2) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("2");
      yield();
      break;
    } else if (digitalRead(switchPin3) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      mymenu.ledpattern = 4;
      ledCallback();
      loop = 0;
      button_press("3");
      yield();
      break;
    } else if (digitalRead(switchPin4) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("4");
      yield();
      break;
    } else {
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println(mymenu.myText);
      display.display();
    }

    for (uint16_t i = 0; i < ledCount; i++)
    {

      if (i % 2 == 0) {
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

    for (uint16_t i = 0; i < ledCount; i++)
      if (i % 2 != 0) {
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
}

void rainbow() {
  mymenu.myText = "   Laissez\n   les bon\n     temps\n    roulez";

  int loop = 1;

  while (loop = 1) {
    if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("1");
      break;
    } else if (digitalRead(switchPin2) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("2");
      break;
    } else if (digitalRead(switchPin3) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      mymenu.ledpattern = 4;
      ledCallback();
      loop = 0;
      button_press("3");
      break;
    } else if (digitalRead(switchPin4) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("4");
      break;
    } else {
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println(mymenu.myText);
      display.display();
    }

    uint8_t time = millis() >> 4;
    for (uint16_t i = 0; i < ledCount; i++) {
      uint8_t p = time - i * 8;
      colors[i] = hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
    }
    ledStrip.write(colors, ledCount, brightness);
    delay(10);
  }
}

void ytCracker() {

  mymenu.myText = "   Laissez\n   les bon\n     temps\n    roulez";

  int loop = 1;

  while (loop = 1) {
    if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("1");
      break;
    } else if (digitalRead(switchPin2) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("2");
      break;
    } else if (digitalRead(switchPin3) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      mymenu.ledpattern = 4;
      ledCallback();
      loop = 0;
      button_press("3");
      break;
    } else if (digitalRead(switchPin4) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      loop = 0;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("4");
      break;
    } else {
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println(mymenu.myText);
      display.display();
    }
    ledStrip.startFrame();
    float power = minPower;
    for (uint16_t i = 0; i < ledCount; i++)
    {
      sendWhite(power);
      power = power * multiplier;
    }
    ledStrip.endFrame(ledCount);
  }
}

void setup() {

  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

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

  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
  pinMode(switchPin4, INPUT_PULLUP);

  mymenu.inv = 1;
  mymenu.page = 1;
  mymenu.total = 4;

  // Configure myThread
  ledThread.onRun(ledCallback);
  ledThread.setInterval(500);

}

void show_menu () {

  display.setTextSize(1);

  // display main menu page
  if (mymenu.page == 1) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("bling");
      display.setTextColor(WHITE);
    } else {
      display.println("bling");
    }
    if (mymenu.inv == 2) {
      display.setTextColor(BLACK, WHITE);
      display.println("network");
      display.setTextColor(WHITE);
    } else {
      display.println("network");
    }
    if (mymenu.inv == 3) {
      display.setTextColor(BLACK, WHITE);
      display.println("games");
      display.setTextColor(WHITE);
    } else {
      display.println("games");
    }
    if (mymenu.inv == 4) {
      display.setTextColor(BLACK, WHITE);
      display.println("about");
      display.setTextColor(WHITE);
    } else {
      display.println("about");
    }
    //display.println(mymenu.inv);
    display.display();
  }

  // all the bling
  if (mymenu.page == 2) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("Cyber Police");
      display.setTextColor(WHITE);
    } else {
      display.println("Cyber Police");
    }
    if (mymenu.inv == 2) {
      display.setTextColor(BLACK, WHITE);
      display.println("rainbow");
      display.setTextColor(WHITE);
    } else {
      display.println("rainbow");
    }
    if (mymenu.inv == 3) {
      display.setTextColor(BLACK, WHITE);
      display.println("white");
      display.setTextColor(WHITE);
    } else {
      display.println("white");
    }
    /*
      if (mymenu.inv == 4) {
      display.setTextColor(BLACK, WHITE);
      display.println("xmas");
      display.setTextColor(WHITE);
      } else {
      display.println("xmas");
      }
      if (mymenu.inv == 5) {
      display.setTextColor(BLACK, WHITE);
      display.println("next");
      display.setTextColor(WHITE);
      } else {
      display.println("next");
      }
    */
    //display.println(mymenu.inv);
    display.display();
  }

  // network
  if (mymenu.page == 3) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("wifi scanner");
      display.setTextColor(WHITE);
    } else {
      display.println("wifi scanner");
    }
    //display.println(mymenu.inv);
    display.display();
  }

  //games games games
  if (mymenu.page == 4) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("burgess pong");
      display.setTextColor(WHITE);
    } else {
      display.println("burgess pong");
    }
    //display.println(mymenu.inv);
    display.display();
  }
}
void loop() {

  controll.run();
  if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    button_press("1");
  } else if (digitalRead(switchPin2) == LOW) {
    button_press("2");
  } else if (digitalRead(switchPin3) == LOW) {
    button_press("3");
  } else if (digitalRead(switchPin4) == LOW) {
    button_press("4");
  } else {
    //do nothing
  }

  show_menu();
}

void burgess_pong() {
  unsigned long start = millis();
  yield();

  display.clearDisplay();
  drawCourt();

  while (millis() - start < 2000);

  display.display();

  ball_update = millis();
  paddle_update = ball_update;

  while (1) {
    yield();
    bool update = false;
    unsigned long time = millis();

    static bool up_state = false;
    static bool down_state = false;

    up_state |= (digitalRead(switchPin1) == LOW);
    down_state |= (digitalRead(switchPin2) == LOW);

    if (time > ball_update) {
      uint8_t new_x = ball_x + ball_dir_x;
      uint8_t new_y = ball_y + ball_dir_y;

      // Check if we hit the vertical walls
      if (new_x == 0 || new_x == 127) {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }

      // Check if we hit the horizontal walls.
      if (new_y == 0 || new_y == 63) {
        ball_dir_y = -ball_dir_y;
        new_y += ball_dir_y + ball_dir_y;
      }

      // Check if we hit the CPU paddle
      if (new_x == CPU_X && new_y >= cpu_y && new_y <= cpu_y + PADDLE_HEIGHT) {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }

      // Check if we hit the player paddle
      if (new_x == PLAYER_X && new_y >= player_y && new_y <= player_y + PADDLE_HEIGHT)
      {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }

      display.drawPixel(ball_x, ball_y, BLACK);
      yield();
      display.drawPixel(new_x, new_y, WHITE);
      yield();
      ball_x = new_x;
      ball_y = new_y;

      ball_update += BALL_RATE;

      update = true;
    }

    if (time > paddle_update) {
      yield();
      paddle_update += PADDLE_RATE;

      // CPU paddle
      display.drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, BLACK);
      const uint8_t half_paddle = PADDLE_HEIGHT >> 1;
      if (cpu_y + half_paddle > ball_y) {
        cpu_y -= 1;
      }
      if (cpu_y + half_paddle < ball_y) {
        cpu_y += 1;
      }
      if (cpu_y < 1) cpu_y = 1;
      if (cpu_y + PADDLE_HEIGHT > 63) cpu_y = 63 - PADDLE_HEIGHT;
      display.drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, WHITE);

      // Player paddle
      display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);
      if (up_state) {
        player_y -= 1;
      }
      if (down_state) {
        player_y += 1;
      }
      up_state = down_state = false;
      if (player_y < 1) player_y = 1;
      if (player_y + PADDLE_HEIGHT > 63) player_y = 63 - PADDLE_HEIGHT;
      display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, WHITE);

      update = true;
    }

    if (update)
      display.display();
  }
}

void drawCourt() {
  yield();
  display.drawRect(0, 0, 128, 64, WHITE);
}

void about() {
  yield();
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setCursor(0, 0);
  display.setTextColor(BLACK, WHITE);
  display.println("Created by the\n DE:AD:10:C5\n");
  display.setTextColor(WHITE);
  display.println("Version: " + version );
  display.println("\n@mzbat");
  display.println("@p0lr_");
  display.println("@theDevilsVoice");
  display.display();

  while (1) {
    yield();
    if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
      mymenu.inv == 1;
      mymenu.page == 1;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("1");
      break;
    } else if (digitalRead(switchPin2) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("2");
      break;
    } else if (digitalRead(switchPin3) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("3");
      break;
    } else if (digitalRead(switchPin4) == LOW) {
      mymenu.inv == 1;
      mymenu.page == 1;
      mymenu.ledpattern = 4;
      ledCallback();
      button_press("4");
      break;
    } else {

    }
  }
}

