/*
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat
   Date   : May 15, 2018
   Version: 0.5
*/
#ifndef MY_BUTT_H
#define MY_BUTT_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "MyGame.h"
#include "MyMenu.h"
#include "nola.h"

class MyButt {
  private:
    int switchPin1 = D3;        // UP
    int switchPin2 = D4;        // DOWN
    int switchPin3 = D7;        // BACK
    int switchPin4 = D10;       // ENTER
  public:
    int button_press(String button_num,
                     MyGame *mygame,
                     MyMenu *mymenu,
                     Nola *mynola,
                     Adafruit_SSD1306 *display);
    int break_butts(MyMenu *mymenu);
};

#endif // MY_BUTT_H
